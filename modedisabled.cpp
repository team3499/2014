#include "modedisabled.h"

#include <Timer.h>

ModeDisabled::ModeDisabled(DriverStation *ds) : ModeBase(ds){
    OUT("Disabled Construct");
}
ModeDisabled::~ModeDisabled(){
    OUT("Disabled Destroy");
}

void ModeDisabled::begin(){
    m_ds->InDisabled(true);
    OUT("Disabled Begin");
    compressor->Stop();
    
    mainLights->setMode(ArduinoControl::Disabled);
}
void ModeDisabled::run(){
    Wait(0.005);
}
void ModeDisabled::end(){
    OUT("Disabled End");
    m_ds->InDisabled(false);
}
