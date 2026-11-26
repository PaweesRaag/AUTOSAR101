#include "autosar101/com.hpp"

namespace autosar101 {

Pdu Com::pack_vehicle_speed(const SignalFrame& signal) {
    Pdu pdu{};
    pdu.pdu_id = kVehicleStatusPduId;
    pdu.length = 2;
    pdu.payload[0] = static_cast<std::uint8_t>((signal.vehicle_speed_kmh >> 8U) & 0xFFU);
    pdu.payload[1] = static_cast<std::uint8_t>(signal.vehicle_speed_kmh & 0xFFU);
    return pdu;
}

std::optional<SignalFrame> Com::unpack_vehicle_speed(const Pdu& pdu) noexcept {
    if (pdu.pdu_id != kVehicleStatusPduId || pdu.length != 2) {
        return std::nullopt;
    }

    const auto high = static_cast<std::uint16_t>(pdu.payload[0]);
    const auto low = static_cast<std::uint16_t>(pdu.payload[1]);
    return SignalFrame{
        static_cast<std::uint16_t>((high << 8U) | low)
    };
}

} // namespace autosar101
