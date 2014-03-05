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
    OUT("Disabled Init");

    mainLights->setModeDisabled();
    mainLights->setTeam((m_ds->GetAlliance() == DriverStation::kRed) ? ArduinoControl::TeamRed : ArduinoControl::TeamBlue);

    compressor->Stop();
}
void ModeDisabled::run(){
    Wait(0.005);
}
void ModeDisabled::end(){
    OUT("Disabled End");
    m_ds->InDisabled(false);
}
