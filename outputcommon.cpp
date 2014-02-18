#include "outputcommon.h"

DriverStationLCD *OutputCommon::dsLCD;
TCPConnection *OutputCommon::tcpc;

Operator *OutputCommon::op; // oper8shunal

DigitalInput *OutputCommon::psensor; // Digital I/O 5
ArduinoControl *OutputCommon::mainLights;

CANJaguar *OutputCommon::jagFR; // Jaguar #3
CANJaguar *OutputCommon::jagFL; // Jaguar #4
CANJaguar *OutputCommon::jagRR; // Jaguar #2
CANJaguar *OutputCommon::jagRL; // Jaguar #5

CANJaguar *OutputCommon::handstilt; // For tilting the arm up and down. #63

Compressor *OutputCommon::compressor; // Relay 2, Digital I/O 2
SolenoidBreakout *OutputCommon::airsys; // Solenoids 1-8
//Relay *OutputCommon::auxpwoer; // Relay 5

void OutputCommon::initCommon(){
    // Initialize
    dsLCD = DriverStationLCD::GetInstance();
    //tcpc = new TCPConnection();

    op = new Operator();
    
    psensor = new DigitalInput(1, 5);
    mainLights  = new ArduinoControl(7);

    jagFR = new CANJaguar(2, CANJaguar::kSpeed);
    jagFL = new CANJaguar(5, CANJaguar::kSpeed);
    jagRR = new CANJaguar(3, CANJaguar::kSpeed);
    jagRL = new CANJaguar(4, CANJaguar::kSpeed);

    handstilt = new CANJaguar(63, CANJaguar::kPercentVbus);

    compressor = new Compressor(2, 2);
    airsys = new SolenoidBreakout();
    //auxpwoer = new Relay(1, 5, Relay::kForwardOnly);
}

void OutputCommon::destroyCommon(){
	delete dsLCD;
	
	delete op;
	
    delete psensor;
    delete mainLights;

    delete jagFR;
    delete jagFL;
    delete jagRR;
    delete jagRL;
    
    delete handstilt;
    
    delete compressor;
    delete airsys;
    //delete auxpwoer;
}
