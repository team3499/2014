#include "outputcommon.h"

DriverStationLCD *OutputCommon::dsLCD;

Compressor *OutputCommon::compressor; // Relay 2, Digital I/O 2
DigitalOutput *OutputCommon::proximityLight; // Digital I/O 8
DigitalInput *OutputCommon::psensor; // Digital I/O 5

CANJaguar *OutputCommon::jagFR; // Jaguar #3
CANJaguar *OutputCommon::jagFL; // Jaguar #4
CANJaguar *OutputCommon::jagRR; // Jaguar #2
CANJaguar *OutputCommon::jagRL; // Jaguar #5

Relay *OutputCommon::cmp; // Relay 5

CANJaguar *OutputCommon::handstilt; // For tilting the arm up and down. #63

SolenoidBreakout *OutputCommon::airsys; // Solenoids 1-8

Joystick *OutputCommon::teststick; // Joystick 1
Operator *OutputCommon::op; // oper8shunal

ArduinoControl *OutputCommon::mainLights;

TCPConnection *OutputCommon::tcpc;
