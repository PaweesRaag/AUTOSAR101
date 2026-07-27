#ifndef RTE_H
#define RTE_H

// ==================================
// RTE Signal Storage
// Stores the switch state signal
// ==================================
bool SeatSwitchSignal = false;

// ==================================
// RTE Write API
//
// Called by SWC A
// ==================================
void Rte_Write_SeatSwitch(bool state)
{
    SeatSwitchSignal = state;
}

// ==================================
// RTE Read API
//
// Called by SWC B
// ==================================
bool Rte_Read_SeatSwitch()
{
    return SeatSwitchSignal;
}

#endif