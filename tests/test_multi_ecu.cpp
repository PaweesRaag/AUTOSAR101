#include "../AUTOSAR/ECU_A/SWC/SeatSwitchSWC.h"
#include "../AUTOSAR/ECU_B/SWC/SeatHeatingSWC.h"
#include <cassert>

int main()
{
    ECU_A::SeatSwitchSWC switchSwc;
    ECU_B::SeatHeatingSWC heatingSwc;

    switchSwc.setSwitch(false);
    switchSwc.run();
    heatingSwc.run();
    assert(!heatingSwc.heaterOn());
    assert(!heatingSwc.ledOn());

    switchSwc.setSwitch(true);
    switchSwc.run();
    heatingSwc.run();
    assert(heatingSwc.heaterOn());
    assert(heatingSwc.ledOn());

    return 0;
}