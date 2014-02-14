
#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include <stdio.h>

class DriverStation;

/**
 * Handle input from Logitech Dual Action Gamepad connected to the Driver
 * Station.
 */
class Gamepad
{
public:
    typedef enum
    {
        kLeftXAxis, kLeftYAxis, kRightXAxis, kRightYAxis,
        kDPadXAxis, kDPadYAxis
    } AxisType;

    typedef enum
    {
        kCenter, kUp, kUpLeft, kLeft, kDownLeft, kDown, kDownRight, kRight,
        kUpRight
    } DPadDirection;

    Gamepad(UINT32 port);
    ~Gamepad();

    float GetLeftX();
    float GetLeftY();
    float GetRightX();
    float GetRightY();
    float GetDPadX(); // needed to add these for pan-drive
    float GetDPadY(); // here too.
    float GetAxis(AxisType axis);
    float GetRawAxis(UINT32 axis);

    bool GetNumberedButton(unsigned buttonNumber);
    bool GetLeftPush(); // These are jostick pushes.
    bool GetRightPush(); // see below drawing
    
    //   _|_
    //   \_/
    //  _____
    //  \   /
    //   | |
    // __| |__
    
    DPadDirection GetDPad();

    double GetLeftTrigger();
    double GetRightTrigger();
    double GetTriggerAxis();

protected:
    static const UINT32 kLeftYAxisNum  = 2;
    static const UINT32 kLeftXAxisNum  = 1;
    static const UINT32 kRightYAxisNum = 5;
    static const UINT32 kRightXAxisNum = 4;
    static const UINT32 kDPadXAxisNum  = 5;
    static const UINT32 kDPadYAxisNum  = 6;
    static const UINT32 kTriggerAxisNum = 3;

    static const unsigned kLeftAnalogStickButton = 9;
    static const unsigned kRightAnalogStickButton = 10;

    DriverStation *ap_ds;
    UINT32 a_port;
};

#endif // GAMEPAD_H_

