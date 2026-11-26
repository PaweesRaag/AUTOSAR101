#include "autosar101/can_if.hpp"
#include "autosar101/com.hpp"
#include "autosar101/pdur.hpp"
#include "autosar101/rte.hpp"

#include <iomanip>
#include <iostream>

int main() {
    using namespace autosar101;

    Rte ecu_a_rte;
    Rte ecu_b_rte;
    CanBus bus;
    CanIf ecu_a_can_if{bus};
    CanIf ecu_b_can_if{bus};

    // ECU A application SWC publishes two typed signals to its local RTE.
    ecu_a_rte.write_vehicle_speed(SignalFrame{85, 2400});
    const auto tx_signals = ecu_a_rte.read_vehicle_speed();
    if (!tx_signals) {
        std::cerr << "ECU A: no vehicle-status sample available\n";
        return 1;
    }

    const auto tx_pdu = Com::pack_vehicle_status(*tx_signals);
    const auto tx_frame = PduR::route_to_can(tx_pdu);
    if (!tx_frame || !ecu_a_can_if.transmit(*tx_frame)) {
        std::cerr << "ECU A: transmit path rejected the PDU\n";
        return 1;
    }

    std::cout << "ECU A transmitted CAN ID 0x"
              << std::hex << tx_frame->can_id << std::dec << " payload:";
    for (std::size_t i = 0; i < tx_frame->dlc; ++i) {
        std::cout << " 0x" << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<unsigned>(tx_frame->data[i]);
    }
    std::cout << std::dec << '\n';

    const auto rx_frame = ecu_b_can_if.receive();
    if (!rx_frame) {
        std::cerr << "ECU B: no CAN frame received\n";
        return 1;
    }

    const auto rx_pdu = PduR::route_from_can(*rx_frame);
    if (!rx_pdu) {
        std::cerr << "ECU B: PduR rejected the CAN frame\n";
        return 1;
    }

    const auto rx_signals = Com::unpack_vehicle_status(*rx_pdu);
    if (!rx_signals) {
        std::cerr << "ECU B: COM rejected the PDU\n";
        return 1;
    }

    ecu_b_rte.write_vehicle_speed(*rx_signals);
    const auto swc_input = ecu_b_rte.read_vehicle_speed();
    if (!swc_input) {
        std::cerr << "ECU B: RTE has no received value\n";
        return 1;
    }

    std::cout << "ECU B application SWC received VehicleSpeed = "
              << swc_input->vehicle_speed_kmh << " km/h, EngineSpeed = "
              << swc_input->engine_speed_rpm << " rpm\n";
    return 0;
}
