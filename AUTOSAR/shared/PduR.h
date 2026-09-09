#ifndef AUTOSAR101_PDUR_H
#define AUTOSAR101_PDUR_H

#include "COM.h"

namespace PduR
{

// Educational routing boundary between COM and lower communication layers.
inline void RouteTransmit(bool signal)
{
    COM::SendSignal(signal);
}

inline bool RouteReceive()
{
    return COM::ReceiveSignal();
}

} // namespace PduR

#endif
