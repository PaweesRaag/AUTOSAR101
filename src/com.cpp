#include "autosar101/com.hpp"

namespace autosar101 {
namespace {

void pack_u16_be(Pdu& pdu, std::size_t offset, std::uint16_t value) {
    pdu.payload[offset] = static_cast<std::uint8_t>((value >> 8U) & 0xFFU);
    pdu.payload[offset + 1] = static_cast<std::uint8_t>(value & 0xFFU);
}

std::uint16_t unpack_u16_be(const Pdu& pdu, std::size_t offset) noexcept {
    const auto high = static_cast<std::uint16_t>(pdu.payload[offset]);
    const auto low = static_cast<std::uint16_t>(pdu.payload[offset + 1]);
    return static_cast<std::uint16_t>((high << 8U) | low);
}

} // namespace

Pdu Com::pack_vehicle_status(const SignalFrame& signals) {
    Pdu pdu{};
    pdu.pdu_id = kVehicleStatusPduId;
    pdu.length = 4;
    pack_u16_be(pdu, 0, signals.vehicle_speed_kmh);
    pack_u16_be(pdu, 2, signals.engine_speed_rpm);
    return pdu;
}

std::optional<SignalFrame> Com::unpack_vehicle_status(const Pdu& pdu) noexcept {
    if (pdu.pdu_id != kVehicleStatusPduId || pdu.length != 4) {
        return std::nullopt;
    }

    return SignalFrame{
        unpack_u16_be(pdu, 0),
        unpack_u16_be(pdu, 2)
    };
}

} // namespace autosar101
