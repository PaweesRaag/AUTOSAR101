#pragma once
#include "../CanIf/CanIf_Types.h"

namespace Can {
void write(const CanIf::CanFrame& frame);
bool read(CanIf::CanFrame& frame);
}