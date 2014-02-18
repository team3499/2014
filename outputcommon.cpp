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

void OutputCommon::initCommon(){
    // Initialize
    dsLCD = DriverStationLCD::GetInstance();

    compressor = new Compressor(2, 2);
    proximityLight = new DigitalOutput(1, 8);
    psensor = new DigitalInput(1, 5);

    cmp = new Relay(1, 5, Relay::kForwardOnly);

    jagFR = new CANJaguar(2, CANJaguar::kSpeed);
    jagFL = new CANJaguar(5, CANJaguar::kSpeed);
    jagRR = new CANJaguar(3, CANJaguar::kSpeed);
    jagRL = new CANJaguar(4, CANJaguar::kSpeed);

    handstilt = new CANJaguar(63, CANJaguar::kPercentVbus);

    airsys = new SolenoidBreakout();
    teststick = new Joystick(3);

    mainLights  = new ArduinoControl(7);
    
    op = new Operator();
}

void OutputCommon::destroyCommon(){
    delete compressor;
    delete proximityLight;
    delete psensor;

    delete jagFR;
    delete jagFL;
    delete jagRR;
    delete jagRL;

    delete handstilt;

    delete airsys;	
}
