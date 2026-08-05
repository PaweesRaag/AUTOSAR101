#include<iostream>
#include "COM.h"

// =================================
// Simulated Communication Buffer
//
// Later this becomes:
// CAN Frame
// UDP Packet
// Ethernet Packet
// =================================
static SignalPDU ComBuffer;

// =================================
// Store signal into PDU
// =================================
void COM::SendSignal(bool state)
{
    ComBuffer.switchState = state;
}

// =================================
// Read signal from PDU
// =================================
bool COM::ReceiveSignal()
{
    return ComBuffer.switchState;
}
