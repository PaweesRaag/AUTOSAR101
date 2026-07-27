#include <iostream>

// =========================
// Receiver Port
// Receives switch state from another SWC through the RTE
// =========================
/*
struct SeatSwitchPort
{
    bool switchState;
};

// =========================
// Provide Port
// Sends heater state to the outside world
// =========================
struct HeaterPort
{
    bool heaterState;
};

// =========================
// Provide Port
// Sends LED state to the outside world
// =========================
struct LedPort
{
    bool ledState;
};
*/

#include "Ports.h"
#include "RTE.h"
// =========================
// SeatHeatingControlSWC
//
// Responsibility:
// 1. Read switch signal from RTE
// 2. Process the signal
// 3. Update heater output
// 4. Update LED output
// =========================
class SeatHeatingControlSWC
{
public:

    // Receiver Port (R-Port)
    SeatSwitchPort input;

    // Provide Ports (P-Ports)
    HeaterPort heaterOutput;
    LedPort ledOutput;

    // =========================
    // Runnable
    //
    // Read signal from RTE and
    // store it in the receiver port
    // =========================
    void ReadSignal()
    {
        // Uncomment once RTE.h exists

         input.switchState = Rte_Read_SeatSwitch();
    }

    // =========================
    // Runnable
    //
    // Process incoming signal and
    // update outputs
    // =========================
    void Process()
    {
        heaterOutput.heaterState = input.switchState;

        ledOutput.ledState = input.switchState;
    }
};
