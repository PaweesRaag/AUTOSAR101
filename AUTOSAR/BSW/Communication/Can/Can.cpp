#include "Can.h"
#include "CanBusSimulator.h"

namespace Can {
void write(const CanIf::CanFrame& frame) { CanBusSimulator::publish(frame); }
bool read(CanIf::CanFrame& frame) { return CanBusSimulator::consume(frame); }
}