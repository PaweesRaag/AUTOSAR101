#pragma once

#include "autosar101/types.hpp"

#include <optional>

namespace autosar101 {

// Static routing configuration for this small single-channel demonstration.
class PduR {
public:
    static constexpr std::uint16_t kVehicleStatusCanId = 0x120;

    [[nodiscard]] static std::optional<CanFrame> route_to_can(const Pdu& pdu) noexcept;
    [[nodiscard]] static std::optional<Pdu> route_from_can(const CanFrame& frame) noexcept;
};

} // namespace autosar101
