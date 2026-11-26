#pragma once

#include "autosar101/types.hpp"

#include <cstddef>
#include <deque>
#include <optional>

namespace autosar101 {

// Deterministic in-process transport. This is not a physical CAN controller
// and does not model arbitration, bit timing, ACK, error frames or bus faults.
class CanBus {
public:
    void transmit(const CanFrame& frame);
    [[nodiscard]] std::optional<CanFrame> receive();
    [[nodiscard]] std::size_t pending_frames() const noexcept;

private:
    std::deque<CanFrame> frames_{};
};

} // namespace autosar101
