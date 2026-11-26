#include "autosar101/can_bus.hpp"

namespace autosar101 {

void CanBus::transmit(const CanFrame& frame) {
    if (frame.dlc <= kCanMaxPayload) {
        frames_.push_back(frame);
    }
}

std::optional<CanFrame> CanBus::receive() {
    if (frames_.empty()) {
        return std::nullopt;
    }

    const auto frame = frames_.front();
    frames_.pop_front();
    return frame;
}

std::size_t CanBus::pending_frames() const noexcept {
    return frames_.size();
}

} // namespace autosar101
