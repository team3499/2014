#include "modebase.h"

ModeBase::ModeBase(DriverStation *ds) : isrun(false), m_ds(ds){
	
}
ModeBase::~ModeBase(){
	
}

void ModeBase::start(){
	if(!isrun){
		init();
		isrun = true;
	}
}
void ModeBase::stop(){
	if(isrun){
		end();
		isrun = false;
	}	
}

void ModeBase::init(){
	OUT("ERROR DEFAULT INIT");
}
void ModeBase::run(){
	OUT("ERROR DEFAULT RUN");
}
void ModeBase::end(){
	OUT("ERROR DEFAULT END");
}
