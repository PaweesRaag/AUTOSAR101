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

class SeatHeatingControl
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

int main()
{
    SeatHeatingControl leftSeat;
    SeatHeatingControl rightSeat;

    std::cout << "Enter the left seat state \n";
    std::cin >> leftSeat.input.switchState;

    std::cout << "Enter the right seat state \n";
    std::cin >> rightSeat.input.switchState;

    leftSeat.Process();
    rightSeat.Process();

    std::cout << "left seat: " << leftSeat.heaterOutput.heaterState << '\n';
    std::cout << "right seat: " << rightSeat.heaterOutput.heaterState << '\n';

    std::cout << "Left LED: " << leftSeat.ledOutput.ledState << '\n';
    std::cout << "Right LED: " << rightSeat.ledOutput.ledState << '\n';

    return 0;
}