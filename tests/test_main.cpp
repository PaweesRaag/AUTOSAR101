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
    const SignalFrame samples[] = {
        {0, 0}, {85, 2400}, {65535, 65535}, {1, 32768}
    };

    for (const auto& sample : samples) {
        const auto pdu = Com::pack_vehicle_status(sample);
        const auto decoded = Com::unpack_vehicle_status(pdu);
        check(decoded && decoded->vehicle_speed_kmh == sample.vehicle_speed_kmh
                       && decoded->engine_speed_rpm == sample.engine_speed_rpm,
              "COM round-trip speed=" + std::to_string(sample.vehicle_speed_kmh)
                  + ", rpm=" + std::to_string(sample.engine_speed_rpm));
    }
}

void test_com_rejects_invalid_pdu() {
    using namespace autosar101;
    auto pdu = Com::pack_vehicle_status(SignalFrame{42, 900});
    pdu.length = 3;
    check(!Com::unpack_vehicle_status(pdu), "COM rejects truncated vehicle-status PDU");
    pdu.length = 5;
    check(!Com::unpack_vehicle_status(pdu), "COM rejects oversized vehicle-status PDU");
    pdu = Com::pack_vehicle_status(SignalFrame{42, 900});
    pdu.pdu_id = 99;
    check(!Com::unpack_vehicle_status(pdu), "COM rejects unknown PDU identifier");
}

void test_pdur_routing() {
    using namespace autosar101;
    const auto pdu = Com::pack_vehicle_status(SignalFrame{1234, 3200});
    const auto frame = PduR::route_to_can(pdu);
    check(frame && frame->can_id == PduR::kVehicleStatusCanId && frame->dlc == 4,
          "PduR maps configured PDU to CAN frame");
    check(frame && PduR::route_from_can(*frame).has_value(),
          "PduR maps received CAN frame to configured PDU");

    auto invalid = *frame;
    invalid.can_id = 0x777;
    check(!PduR::route_from_can(invalid), "PduR rejects unknown CAN identifier");
    invalid = *frame;
    invalid.dlc = 9;
    check(!PduR::route_from_can(invalid), "PduR rejects invalid CAN DLC");
    auto invalid_pdu = pdu;
    invalid_pdu.length = 9;
    check(!PduR::route_to_can(invalid_pdu), "PduR rejects payload longer than classic CAN");
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

    ecu_a.write_vehicle_speed(SignalFrame{246, 4100});
    const auto signals = ecu_a.read_vehicle_speed();
    const auto pdu = signals ? Com::pack_vehicle_status(*signals) : Pdu{};
    const auto frame = PduR::route_to_can(pdu);
    const bool sent = frame && can_a.transmit(*frame);
    const auto received_frame = can_b.receive();
    const auto received_pdu = received_frame ? PduR::route_from_can(*received_frame) : std::nullopt;
    const auto received_signals = received_pdu ? Com::unpack_vehicle_status(*received_pdu) : std::nullopt;
    if (received_signals) {
        ecu_b.write_vehicle_speed(*received_signals);
    }
    const auto app_value = ecu_b.read_vehicle_speed();

    check(sent && app_value && app_value->vehicle_speed_kmh == 246
                    && app_value->engine_speed_rpm == 4100,
          "end-to-end ECU A -> bus -> ECU B transfers both signals");
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
