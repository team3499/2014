#include "modebase.h"

ModeBase::ModeBase(DriverStation *ds) : isrun(false), m_ds(ds){
    
}
ModeBase::~ModeBase(){
    
}

void ModeBase::start(){
    if(!isrun){
        begin();
        isrun = true;
    }
}
void ModeBase::stop(){
    if(isrun){
        end();
        isrun = false;
    }    
}

void ModeBase::begin(){
    OUT("ERROR DEFAULT BEGIN");
}
void ModeBase::run(){
    OUT("ERROR DEFAULT RUN");
}
void ModeBase::end(){
    OUT("ERROR DEFAULT END");
}

const char *ModeBase::typeString(){
    OUT("ERROR DEFAULT TYPESTRING");
    return "Base!";
}
