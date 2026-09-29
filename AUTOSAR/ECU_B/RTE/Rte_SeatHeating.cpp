#include "Rte_SeatHeating.h"
#include "../../BSW/Communication/Com/Com.h"

namespace ECU_B::Rte {
bool readSeatSwitch(bool& enabled)
{
    Com::SeatSwitchSignal signal{};
    if (!Com::receiveSeatSwitch(signal)) return false;
    enabled = signal.enabled;
    return true;
}
}
