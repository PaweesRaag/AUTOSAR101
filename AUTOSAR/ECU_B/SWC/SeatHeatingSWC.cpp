#include "SeatHeatingSWC.h"
#include "../../BSW/Communication/Com/Com.h"

namespace ECU_B {
void SeatHeatingSWC::run() {
    Com::SeatSwitchSignal signal{};
    if (!Com::receiveSeatSwitch(signal)) return;
    heaterOn_ = signal.enabled;
    ledOn_ = signal.enabled;
}
bool SeatHeatingSWC::heaterOn() const { return heaterOn_; }
bool SeatHeatingSWC::ledOn() const { return ledOn_; }
}