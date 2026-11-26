#include "autosar101/can_if.hpp"
#include "autosar101/com.hpp"
#include "autosar101/pdur.hpp"
#include "autosar101/rte.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

int failures = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "[PASS] " << name << '\n';
    } else {
        std::cerr << "[FAIL] " << name << '\n';
        ++failures;
    }
}

void test_com_round_trip() {
    using namespace autosar101;
    for (const auto value : {std::uint16_t{0}, std::uint16_t{85}, std::uint16_t{65535}}) {
        const auto decoded = Com::unpack_vehicle_speed(
            Com::pack_vehicle_speed(SignalFrame{value}));
        check(decoded && decoded->vehicle_speed_kmh == value,
              "COM round-trip value " + std::to_string(value));
    }
}

void test_com_rejects_invalid_pdu() {
    using namespace autosar101;
    auto pdu = Com::pack_vehicle_speed(SignalFrame{42});
    pdu.length = 1;
    check(!Com::unpack_vehicle_speed(pdu), "COM rejects incorrect payload length");
    pdu = Com::pack_vehicle_speed(SignalFrame{42});
    pdu.pdu_id = 99;
    check(!Com::unpack_vehicle_speed(pdu), "COM rejects unknown PDU identifier");
}

void test_pdur_routing() {
    using namespace autosar101;
    const auto pdu = Com::pack_vehicle_speed(SignalFrame{1234});
    const auto frame = PduR::route_to_can(pdu);
    check(frame && frame->can_id == PduR::kVehicleStatusCanId && frame->dlc == 2,
          "PduR maps configured PDU to CAN frame");
    check(frame && PduR::route_from_can(*frame).has_value(),
          "PduR maps received CAN frame to configured PDU");

    auto invalid = *frame;
    invalid.can_id = 0x777;
    check(!PduR::route_from_can(invalid), "PduR rejects unknown CAN identifier");
}

void test_bus_fifo_and_empty() {
    using namespace autosar101;
    CanBus bus;
    CanFrame first{};
    first.can_id = 0x120;
    first.dlc = 1;
    first.data[0] = 0x11;
    CanFrame second = first;
    second.data[0] = 0x22;

    check(!bus.receive(), "CAN bus reports empty receive queue");
    bus.transmit(first);
    bus.transmit(second);
    const auto rx1 = bus.receive();
    const auto rx2 = bus.receive();
    check(rx1 && rx1->data[0] == 0x11 && rx2 && rx2->data[0] == 0x22,
          "CAN bus preserves FIFO frame order");
    check(bus.pending_frames() == 0, "CAN bus queue drains correctly");
}

void test_canif_rejects_invalid_dlc() {
    using namespace autosar101;
    CanBus bus;
    CanIf can_if{bus};
    CanFrame invalid{};
    invalid.dlc = 9;
    check(!can_if.transmit(invalid), "CanIf rejects DLC greater than eight");
    check(bus.pending_frames() == 0, "invalid frame is not queued");
}

void test_end_to_end_two_ecus() {
    using namespace autosar101;
    Rte ecu_a;
    Rte ecu_b;
    CanBus bus;
    CanIf can_a{bus};
    CanIf can_b{bus};

    ecu_a.write_vehicle_speed(SignalFrame{246});
    const auto signal = ecu_a.read_vehicle_speed();
    const auto pdu = signal ? Com::pack_vehicle_speed(*signal) : Pdu{};
    const auto frame = PduR::route_to_can(pdu);
    const bool sent = frame && can_a.transmit(*frame);
    const auto received_frame = can_b.receive();
    const auto received_pdu = received_frame ? PduR::route_from_can(*received_frame) : std::nullopt;
    const auto received_signal = received_pdu ? Com::unpack_vehicle_speed(*received_pdu) : std::nullopt;
    if (received_signal) {
        ecu_b.write_vehicle_speed(*received_signal);
    }
    const auto app_value = ecu_b.read_vehicle_speed();

    check(sent && app_value && app_value->vehicle_speed_kmh == 246,
          "end-to-end ECU A -> bus -> ECU B signal transfer");
}

} // namespace

int main() {
    test_com_round_trip();
    test_com_rejects_invalid_pdu();
    test_pdur_routing();
    test_bus_fifo_and_empty();
    test_canif_rejects_invalid_dlc();
    test_end_to_end_two_ecus();

    if (failures != 0) {
        std::cerr << failures << " test(s) failed\n";
        return EXIT_FAILURE;
    }
    std::cout << "All AUTOSAR101 tests passed\n";
    return EXIT_SUCCESS;
}
