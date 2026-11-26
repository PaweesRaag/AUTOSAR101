#pragma once

#include "autosar101/types.hpp"

#include <optional>

namespace autosar101 {

// Educational sender-receiver data access abstraction for one ECU.
// A generated AUTOSAR RTE is configuration-specific and substantially richer.
class Rte {
public:
    void write_vehicle_speed(const SignalFrame& value) noexcept {
        vehicle_speed_ = value;
    }

    [[nodiscard]] std::optional<SignalFrame> read_vehicle_speed() const noexcept {
        return vehicle_speed_;
    }

private:
    std::optional<SignalFrame> vehicle_speed_{};
};

} // namespace autosar101
