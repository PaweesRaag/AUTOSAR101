#include "swcB.cpp"

int main()
{
    SeatHeatingControlSWC heaterSwc;

    heaterSwc.ReadSignal();

    heaterSwc.Process();

    heaterSwc.Display();

    return 0;
}
