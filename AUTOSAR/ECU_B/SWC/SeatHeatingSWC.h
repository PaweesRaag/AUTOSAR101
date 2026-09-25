#pragma once

namespace ECU_B {
class SeatHeatingSWC {
public:
    void run();
    bool heaterOn() const;
    bool ledOn() const;
private:
    bool heaterOn_{false};
    bool ledOn_{false};
};
}