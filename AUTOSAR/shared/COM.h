#ifndef COM_H
#define COM_H

// =================================
// Signal PDU
//
// COM transports PDUs
// not raw application signals
// =================================
struct SignalPDU
{
    bool switchState;
};

// =================================
// COM Layer
// =================================
class COM
{
public:

    // Pack Signal -> PDU
    static void SendSignal(bool state);

    // Unpack PDU -> Signal
    static bool ReceiveSignal();
};

#endif