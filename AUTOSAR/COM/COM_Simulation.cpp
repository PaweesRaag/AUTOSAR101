#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/*
 * AUTOSAR101 — Simplified COM Stack Simulation
 *
 * This example builds on the existing SWC/RTE examples and introduces the
 * next important abstraction: inter-ECU communication.
 *
 * Conceptual flow:
 *
 *   Application SWC
 *        |
 *       RTE
 *        |
 *       COM
 *        |
 *       PDU
 *        |
 *   PDU Router (conceptual)
 *        |
 *     CAN Bus
 *
 * This is NOT an AUTOSAR implementation. It is a small educational model
 * used to understand the responsibility boundaries between application data,
 * signals, PDUs and the transport medium.
 */

struct VehicleSpeedSignal
{
    std::uint16_t speedKmh;
};

/*
 * A PDU is a container that carries one or more signals.
 *
 * Real AUTOSAR COM performs packing/unpacking according to configuration.
 * Here we model a tiny PDU with two bytes of payload.
 */
struct VehicleStatusPdu
{
    std::uint16_t canId;
    std::vector<std::uint8_t> payload;
};

/*
 * Simplified COM module.
 *
 * Responsibility:
 *   Application-facing signal data -> PDU payload
 *
 * In a real stack, COM would also deal with configured signals, update bits,
 * transmission modes, deadlines, filtering, endianness and other behavior.
 */
class Com
{
public:
    static VehicleStatusPdu PackVehicleSpeed(const VehicleSpeedSignal& signal)
    {
        VehicleStatusPdu pdu;
        pdu.canId = 0x120;

        // Split the 16-bit signal into two bytes.
        // This example uses big-endian/network-order packing explicitly so
        // that the representation is visible to the learner.
        const auto high = static_cast<std::uint8_t>((signal.speedKmh >> 8) & 0xFF);
        const auto low  = static_cast<std::uint8_t>(signal.speedKmh & 0xFF);

        pdu.payload = {high, low};
        return pdu;
    }

    static VehicleSpeedSignal UnpackVehicleSpeed(const VehicleStatusPdu& pdu)
    {
        if (pdu.payload.size() < 2)
        {
            throw std::runtime_error("PDU payload is too small for VehicleSpeed");
        }

        VehicleSpeedSignal signal{};
        signal.speedKmh =
            (static_cast<std::uint16_t>(pdu.payload[0]) << 8) |
            static_cast<std::uint16_t>(pdu.payload[1]);

        return signal;
    }
};

class PduRouter
{
public:
    static VehicleStatusPdu Route(const VehicleStatusPdu& pdu)
    {
        // Real PduR performs configured PDU routing between upper and lower
        // communication modules. Our simulation simply forwards the PDU.
        return pdu;
    }
};

class CanBus
{
public:
    static VehicleStatusPdu Transmit(const VehicleStatusPdu& pdu)
    {
        // A real CAN driver/interface would interact with a CAN controller.
        // This educational model represents the bus as a simple transport.
        return pdu;
    }
};

static void PrintPdu(const VehicleStatusPdu& pdu)
{
    std::cout << "CAN ID: 0x"
              << std::hex << pdu.canId
              << std::dec << '\n';

    std::cout << "Payload: ";

    for (const auto byte : pdu.payload)
    {
        std::cout << "0x"
                  << std::hex
                  << std::setw(2)
                  << std::setfill('0')
                  << static_cast<int>(byte)
                  << ' ';
    }

    std::cout << std::dec << "\n";
}

int main()
{
    /*
     * ECU A — Application Layer
     *
     * The application only thinks in terms of a meaningful signal:
     * "vehicle speed = 85 km/h".
     */
    VehicleSpeedSignal senderSignal{85};

    std::cout << "ECU A application signal: "
              << senderSignal.speedKmh
              << " km/h\n\n";

    /*
     * RTE -> COM
     *
     * In a real AUTOSAR system the RTE/API boundary and configured COM
     * interfaces would connect the SWC to COM. Here we directly call the
     * educational COM model.
     */
    const auto pdu = Com::PackVehicleSpeed(senderSignal);

    /*
     * COM -> PduR -> CAN
     *
     * The application signal has now become a transport PDU.
     */
    const auto routedPdu = PduRouter::Route(pdu);
    const auto receivedPdu = CanBus::Transmit(routedPdu);

    std::cout << "Transmitted PDU:\n";
    PrintPdu(receivedPdu);

    /*
     * Receiving ECU
     *
     * The receiving side reverses the process:
     *
     *   CAN -> PduR -> COM -> RTE -> SWC
     */
    const auto receivedSignal = Com::UnpackVehicleSpeed(receivedPdu);

    std::cout << "\nECU B received signal: "
              << receivedSignal.speedKmh
              << " km/h\n";

    return 0;
}
