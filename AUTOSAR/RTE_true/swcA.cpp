#include <iostream>

// =========================
// Sender Port
//
// Provides switch state to other SWCs
// through the RTE
// =========================
/*
struct SeatSwitchPort
{
    bool switchState;
};
*/
#include "Ports.h"
#include "RTE.h"

// =========================
// SeatSwitchSWC
//
// Responsibility:
// 1. Read switch input
// 2. Store switch state
// 3. Publish switch state to RTE
// =========================
class SeatSwitchSWC
{
public:

    // Sender Port (P-Port)
    //
    // Holds the switch state that will
    // be transmitted to another SWC
    SeatSwitchPort switchOutput;

    // =========================
    // Runnable
    //
    // Reads switch state from the user
    // (simulating a hardware switch)
    // =========================
    void ReadSwitch()
    {
        std::cin >> switchOutput.switchState;
    }

    // =========================
    // Runnable
    //
    // Publishes the switch signal
    // to the RTE
    // =========================
    void Process()
    {
        // Uncomment when RTE.h exists

         Rte_Write_SeatSwitch(
             switchOutput.switchState
         );
    }
};