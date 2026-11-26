#pragma once

#include "autosar101/types.hpp"

#include <optional>

namespace autosar101 {

class Com {
public:
    static constexpr std::uint16_t kVehicleStatusPduId = 0x0001;

    // Encodes vehicle speed as an unsigned 16-bit, big-endian signal.
    [[nodiscard]] static Pdu pack_vehicle_speed(const SignalFrame& signal);
    [[nodiscard]] static std::optional<SignalFrame> unpack_vehicle_speed(const Pdu& pdu) noexcept;
};

} // namespace autosar101
