#include "SeatSwitchSWC.h"
#include "../../BSW/Communication/Com/Com.h"

namespace ECU_A {
void SeatSwitchSWC::setSwitch(bool enabled) { switchState_ = enabled; }
bool SeatSwitchSWC::readSwitch() const { return switchState_; }
void SeatSwitchSWC::run() { Com::transmitSeatSwitch({switchState_}); }
}