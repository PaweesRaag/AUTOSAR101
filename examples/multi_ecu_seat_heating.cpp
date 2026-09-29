#include "../AUTOSAR/ECU_A/SWC/SeatSwitchSWC.h"
#include "../AUTOSAR/ECU_B/SWC/SeatHeatingSWC.h"
#include <iostream>

int main()
{
    ECU_A::SeatSwitchSWC switchSwc;
    ECU_B::SeatHeatingSWC heatingSwc;

    switchSwc.setSwitch(true);
    switchSwc.run();
    heatingSwc.run();

    std::cout << "=== AUTOSAR101 Multi-ECU Seat Heating Demo ===\n";
    std::cout << "ECU_A SeatSwitchSWC : " << switchSwc.readSwitch() << "\n";
    std::cout << "ECU_B SeatHeatingSWC: heater=" << heatingSwc.heaterOn()
              << " led=" << heatingSwc.ledOn() << "\n";

    return (heatingSwc.heaterOn() && heatingSwc.ledOn()) ? 0 : 1;
}