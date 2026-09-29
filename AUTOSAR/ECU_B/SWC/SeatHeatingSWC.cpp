#include "SeatHeatingSWC.h"
#include "../RTE/Rte_SeatHeating.h"

namespace ECU_B {
void SeatHeatingSWC::run() {
    bool enabled{};
    if (!Rte::readSeatSwitch(enabled)) return;
    heaterOn_ = enabled;
    ledOn_ = enabled;
}
bool SeatHeatingSWC::heaterOn() const { return heaterOn_; }
bool SeatHeatingSWC::ledOn() const { return ledOn_; }
}
