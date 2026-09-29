#include "CanBusSimulator.h"
#include <optional>

namespace {
std::optional<CanIf::CanFrame> g_frame;
}

namespace CanBusSimulator {
void publish(const CanIf::CanFrame& frame) { g_frame = frame; }

bool consume(CanIf::CanFrame& frame) {
    if (!g_frame) return false;
    frame = *g_frame;
    g_frame.reset();
    return true;
}
}