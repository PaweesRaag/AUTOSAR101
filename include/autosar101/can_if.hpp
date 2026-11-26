#pragma once

#include "autosar101/can_bus.hpp"

#include <optional>

namespace autosar101 {

// Hardware-independent boundary around the simulated bus.
class CanIf {
public:
    explicit CanIf(CanBus& bus) noexcept : bus_(bus) {}

    [[nodiscard]] bool transmit(const CanFrame& frame);
    [[nodiscard]] std::optional<CanFrame> receive();

private:
    CanBus& bus_;
};

} // namespace autosar101
