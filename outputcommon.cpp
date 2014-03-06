#include "outputcommon.h"

DriverStationLCD *OutputCommon::dsLCD;

Operator *OutputCommon::op; // oper8shunal

DigitalInput *OutputCommon::psensor; // Digital I/O 5
ArduinoControl *OutputCommon::mainLights;

DriveSys *OutputCommon::drivesys;

CANJaguar *OutputCommon::handstilt; // For tilting the arm up and down. #63

Compressor *OutputCommon::compressor; // Relay 2, Digital I/O 2
SolenoidBreakout *OutputCommon::airsys; // Solenoids 1-8

void OutputCommon::initCommon(){
    // Initialize
    dsLCD = DriverStationLCD::GetInstance();

    op = new Operator();
    
    psensor = new DigitalInput(1, 5);
    mainLights  = new ArduinoControl(7);
    
    drivesys = new DriveSys(op);

    handstilt = new CANJaguar(63, CANJaguar::kPercentVbus);

    compressor = new Compressor(2, 2);
    airsys = new SolenoidBreakout();
}

void OutputCommon::destroyCommon(){
    delete dsLCD;
    
    delete op;
    
    delete psensor;
    delete mainLights;

    delete drivesys;
    
    delete handstilt;
    
    delete compressor;
    delete airsys;
}
