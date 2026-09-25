#pragma once
#include "../CanIf/CanIf_Types.h"

namespace CanBusSimulator {
void publish(const CanIf::CanFrame& frame);
bool consume(CanIf::CanFrame& frame);
}