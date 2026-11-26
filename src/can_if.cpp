#include "autosar101/can_if.hpp"

namespace autosar101 {

bool CanIf::transmit(const CanFrame& frame) {
    if (frame.dlc > kCanMaxPayload) {
        return false;
    }
    bus_.transmit(frame);
    return true;
}

std::optional<CanFrame> CanIf::receive() {
    return bus_.receive();
}

} // namespace autosar101
