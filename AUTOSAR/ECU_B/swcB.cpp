#include <iostream>
#include "Ports.h"
#include "RTE.h"

// ==================================
// SeatHeatingControlSWC
//
// Receives switch state from RTE
// Controls heater and LED
// ==================================
class SeatHeatingControlSWC
{
public:

    // R-Port
    SeatSwitchPort input;

    // P-Ports
    HeaterPort heaterOutput;
    LedPort ledOutput;

    // Read signal from RTE
    void ReadSignal()
    {
        input.switchState =
            Rte_Read_SeatSwitch();
    }

    // Business logic
    void Process()
    {
        heaterOutput.heaterState =
            input.switchState;

        ledOutput.ledState =
            input.switchState;
    }

    // Diagnostic display
    void Display()
    {
        std::cout << "\nECU_B\n";

        std::cout << "Heater State: "
                  << heaterOutput.heaterState
                  << '\n';

        std::cout << "LED State: "
                  << ledOutput.ledState
                  << '\n';
    }
};