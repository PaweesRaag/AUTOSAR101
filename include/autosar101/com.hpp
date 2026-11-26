#pragma once

#include "autosar101/types.hpp"

#include <optional>

namespace autosar101 {

class Com {
public:
    static constexpr std::uint16_t kVehicleStatusPduId = 0x0001;

    // Encodes speed and engine RPM as two unsigned 16-bit big-endian signals.
    [[nodiscard]] static Pdu pack_vehicle_status(const SignalFrame& signals);
    [[nodiscard]] static std::optional<SignalFrame> unpack_vehicle_status(const Pdu& pdu) noexcept;
};

} // namespace autosar101
