#pragma once

namespace ECU_A {
class SeatSwitchSWC {
public:
    void setSwitch(bool enabled);
    bool readSwitch() const;
    void run();
private:
    bool switchState_{false};
};
}