#pragma once
#include "../PduR/PduR.h"

namespace Com {
struct SeatSwitchSignal {
    bool enabled{};
};
void transmitSeatSwitch(const SeatSwitchSignal& signal);
bool receiveSeatSwitch(SeatSwitchSignal& signal);
}