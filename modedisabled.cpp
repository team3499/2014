#include "modedisabled.h"

#include <Timer.h>

ModeDisabled::ModeDisabled(){
	
}
ModeDisabled::~ModeDisabled(){
	
}

void ModeDisabled::start(){
    printf("$$FRC3499$$ - Disabled Init\n");
    compressor->Stop();
}
void ModeDisabled::run(){
	Wait(0.005);
}
void ModeDisabled::end(){
	
}
