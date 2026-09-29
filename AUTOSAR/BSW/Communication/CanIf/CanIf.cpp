#include "CanIf.h"
#include "../Can/Can.h"

namespace CanIf {
void transmit(const CanFrame& frame) { Can::write(frame); }
bool receive(CanFrame& frame) { return Can::read(frame); }
}