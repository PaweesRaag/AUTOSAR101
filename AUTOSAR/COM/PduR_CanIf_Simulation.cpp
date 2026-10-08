#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

/*
 * AUTOSAR101 — Simplified PduR + CanIf Simulation
 *
 * This module extends COM_Simulation.cpp.
 *
 * Previous example:
 *
 *   SWC
 *    |
 *   RTE
 *    |
 *   COM
 *    |
 *   PDU
 *
 * This example continues downward:
 *
 *   COM
 *    |
 *   PduR
 *    |
 *  CanIf
 *    |
 * CAN Driver / Controller
 *
 * The goal is NOT to reproduce AUTOSAR APIs exactly.
 * The goal is to make the responsibility of each layer concrete.
 */

/*
 * A tiny representation of a CAN PDU.
 *
 * In a real AUTOSAR configuration, a PDU has configured attributes such
 * as an identifier, length and payload layout.
 */
struct CanPdu
{
    std::uint16_t canId;
    std::vector<std::uint8_t> payload;
};

/*
 * PduR — PDU Router
 *
 * Main responsibility:
 *   Route PDUs between upper communication modules and lower interfaces.
 *
 * The important idea is that the upper layer should not need to know which
 * lower communication interface actually carries the PDU.
 */
class PduR
{
public:
    static CanPdu RouteToCan(const CanPdu& pdu)
    {
        std::cout << "[PduR] Routing PDU to CAN interface\n";
        return pdu;
    }

    static CanPdu RouteFromCan(const CanPdu& pdu)
    {
        std::cout << "[PduR] Routing received CAN PDU upward\n";
        return pdu;
    }
};

/*
 * CanIf — CAN Interface
 *
 * Main responsibility:
 *   Provide a hardware-independent interface between upper AUTOSAR
 *   communication modules and the CAN driver.
 *
 * Think of CanIf as the abstraction boundary that prevents PduR/COM from
 * directly depending on one particular CAN controller implementation.
 */
class CanIf
{
public:
    static void Transmit(const CanPdu& pdu)
    {
        std::cout << "[CanIf] Transmitting CAN PDU\n";
        PrintPdu(pdu);
    }

    static CanPdu Receive(const CanPdu& pdu)
    {
        std::cout << "[CanIf] Received CAN PDU from CAN driver\n";
        return pdu;
    }

private:
    static void PrintPdu(const CanPdu& pdu)
    {
        std::cout << "  CAN ID : 0x"
                  << std::hex
                  << pdu.canId
                  << std::dec
                  << '\n';

        std::cout << "  Data   : ";

        for (const auto byte : pdu.payload)
        {
            std::cout << "0x"
                      << std::hex
                      << std::setw(2)
                      << std::setfill('0')
                      << static_cast<int>(byte)
                      << ' ';
        }

        std::cout << std::dec << '\n';
    }
};

/*
 * This function represents COM producing a PDU.
 *
 * Keeping this small makes the layering visible:
 *
 *   Application data -> COM -> PDU
 */
CanPdu ComCreatePdu(std::uint16_t vehicleSpeed)
{
    CanPdu pdu;

    // Example configured CAN identifier.
    pdu.canId = 0x120;

    // Pack the 16-bit vehicle-speed signal into two bytes.
    pdu.payload.push_back(
        static_cast<std::uint8_t>((vehicleSpeed >> 8) & 0xFF));

    pdu.payload.push_back(
        static_cast<std::uint8_t>(vehicleSpeed & 0xFF));

    return pdu;
}

int main()
{
    /*
     * Sender ECU
     *
     * At the application level, the developer thinks in terms of a
     * meaningful signal rather than raw CAN bytes.
     */
    const std::uint16_t vehicleSpeed = 85;

    std::cout << "Application signal: VehicleSpeed = "
              << vehicleSpeed
              << " km/h\n\n";

    /*
     * COM converts the application signal into a PDU.
     */
    const CanPdu txPdu = ComCreatePdu(vehicleSpeed);

    /*
     * PduR receives the PDU from the upper communication layer and selects
     * the configured CAN path.
     */
    const CanPdu routedPdu = PduR::RouteToCan(txPdu);

    /*
     * CanIf is the abstraction boundary to the CAN driver.
     */
    CanIf::Transmit(routedPdu);

    std::cout << "\n--- Receiving ECU ---\n";

    /*
     * In this educational model, the transmitted PDU is immediately
     * presented to the receiving side.
     *
     * Real hardware would involve the CAN controller, CAN driver,
     * interrupts/callbacks and lower-layer processing.
     */
    const CanPdu receivedFromDriver = CanIf::Receive(routedPdu);

    /*
     * CanIf passes the received PDU upward to PduR.
     */
    const CanPdu receivedPdu = PduR::RouteFromCan(receivedFromDriver);

    /*
     * COM would normally unpack the PDU into configured signals.
     * For the educational example, decode the two-byte speed signal here.
     */
    if (receivedPdu.payload.size() < 2)
    {
        std::cerr << "Invalid PDU: expected at least two payload bytes\n";
        return 1;
    }

    const std::uint16_t decodedSpeed =
        (static_cast<std::uint16_t>(receivedPdu.payload[0]) << 8) |
        static_cast<std::uint16_t>(receivedPdu.payload[1]);

    std::cout << "Decoded VehicleSpeed = "
              << decodedSpeed
              << " km/h\n";

    return 0;
}
