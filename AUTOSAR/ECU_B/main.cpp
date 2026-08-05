#include "swcB.cpp"
#include "../shared/COM.h"

int main()
{
    SeatHeatingControlSWC heaterSwc;

    heaterSwc.ReadSignal();

    heaterSwc.Process();

    Rte_Write_SeatSwitch(
    COM::ReceiveSignal()
    );

    heaterSwc.Display();

    return 0;
}
