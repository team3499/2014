#include "outputcommon.h"

#include "ports.h"

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
    
    psensor = new DigitalInput(MAIN_SIDECAR, PROXIMITY_SENSOR_DIO);
    mainLights  = new ArduinoControl(ARDUINO_LIGHT_MODE_PWM, ARDUINO_LIGHT_COLOR_DIO);
    
    drivesys = new DriveSys(op);

    handstilt = new CANJaguar(JAGUAR_HANDS_CAN, CANJaguar::kPercentVbus);

    compressor = new Compressor(MAIN_SIDECAR, COMPRESSOR_TRANSDUCER_DIO, MAIN_SIDECAR, COMPRESSOR_RELAY);
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
