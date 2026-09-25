#pragma once
#include "CanIf_Types.h"

namespace CanIf {
void transmit(const CanFrame& frame);
bool receive(CanFrame& frame);
}