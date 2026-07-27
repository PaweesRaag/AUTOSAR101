#include<iostream>

class SeatHeatingControl
{
private:
    bool heater;
    bool led;

public:
    void Process(bool switchState)
    {
        heater = switchState;
        led = switchState;
    }

    void Display()
    {
        std::cout << "Heater: " << heater << '\n';
        std::cout << "LED: " << led << '\n';
    }
};

int main(){
    SeatHeatingControl leftSeat;
    SeatHeatingControl rightSeat;
    bool leftSwitch;
    bool rightSwitch;

    std::cout << "Enter left seat state \n";
    std::cin >> leftSwitch;
    std::cout << "Enter right seat state \n";
    std::cin >> rightSwitch;

    leftSeat.Process(leftSwitch);
    rightSeat.Process(rightSwitch);

    std::cout << "Left Seat \n";
    leftSeat.Display();
    std::cout << '\n';
    std::cout << "Right Seat \n";
    rightSeat.Display();

}
