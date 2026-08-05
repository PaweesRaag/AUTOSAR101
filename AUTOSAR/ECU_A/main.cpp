#include<iostream>
#include "RTE.h"
#include "Ports.h"
#include "swcA.cpp"
//#include "swcB.cpp"
#include "../shared/COM.h"
int main()
{
    SeatSwitchSWC switchSwc;
    //SeatHeatingControlSWC heaterSwc;

    std::cout << "Enter switch state (0/1): ";

    switchSwc.ReadSwitch();

    switchSwc.Process();

    // RTE -> COM
    COM::SendSignal(
    Rte_Read_SeatSwitch()
    );

    //heaterSwc.ReadSignal();

    //heaterSwc.Process();

    //std::cout << "\nHeater State: "
      //        << heaterSwc.heaterOutput.heaterState
        //      << '\n';

    //std::cout << "LED State: "
      //        << heaterSwc.ledOutput.ledState
        //      << '\n';

    return 0;
}