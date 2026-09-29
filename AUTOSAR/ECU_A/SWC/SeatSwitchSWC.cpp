#include "SeatSwitchSWC.h"
#include "../RTE/Rte_SeatSwitch.h"

namespace ECU_A {
void SeatSwitchSWC::setSwitch(bool enabled) { switchState_ = enabled; }
bool SeatSwitchSWC::readSwitch() const { return switchState_; }
void SeatSwitchSWC::run() { Rte::writeSeatSwitch(switchState_); }
}
