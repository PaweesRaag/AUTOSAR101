#include <iostream>

struct SeatSwitchPort
{
    bool switchState;
};

struct HeaterPort
{
    bool heaterState;
};

struct LedPort
{
    bool ledState;
};

class SeatHeatingControlSWC
{
public:

    SeatSwitchPort input;

    HeaterPort heaterOutput;

    LedPort ledOutput;

    void Process()
    {
        heaterOutput.heaterState = input.switchState;
        ledOutput.ledState = input.switchState;
    }
};

class SeatSwitchSWC
{
public:

    SeatSwitchPort switchOutput;

    void ReadSwitch()
    {
        std::cin >> switchOutput.switchState;
    }
};

int main()
{
    SeatSwitchSWC leftSwitch;
    SeatSwitchSWC rightSwitch;

    SeatHeatingControlSWC leftSeat;
    SeatHeatingControlSWC rightSeat;

    std::cout << "Enter the left seat state (0/1)\n";
    leftSwitch.ReadSwitch();

    std::cout << "Enter the right seat state (0/1)\n";
    rightSwitch.ReadSwitch();

    // Pseudo RTE communication
    leftSeat.input.switchState =
        leftSwitch.switchOutput.switchState;

    rightSeat.input.switchState =
        rightSwitch.switchOutput.switchState;

    leftSeat.Process();
    rightSeat.Process();

    std::cout << "\nLEFT SEAT\n";
    std::cout << "Heater: "
              << leftSeat.heaterOutput.heaterState
              << '\n';

    std::cout << "LED: "
              << leftSeat.ledOutput.ledState
              << '\n';

    std::cout << "\nRIGHT SEAT\n";
    std::cout << "Heater: "
              << rightSeat.heaterOutput.heaterState
              << '\n';

    std::cout << "LED: "
              << rightSeat.ledOutput.ledState
              << '\n';

    return 0;
}