#include "operator.h"


Operator::Operator(){
}

void Operator::regAction(unsigned int button, void (*press)(), void (*release)(), void (*time)(), unsigned int timeout){
    if(presses[button] != NULL){
    	unregAction(button);
    	printf("Forcing unregister of action by assigning without unregistering!\nButton %d\n", button);
    }
    presses[button]      = press;
    releases[button]     = release;
    timeoutcalls[button] = time;
    timeouts[button]     = timeout;
}

void Operator::unregAction(unsigned int button){
	// Dont delete the function!
	presses[button]      = NULL;
	releases[button]     = NULL;
	timeoutcalls[button] = NULL;
}

// There is:
// data - the current states
// lastdata - the previous current states
// presses - whether the button has been pressed down already


void Operator::update(){
	// Check to see if we need to call anything on a button push
	jsBaseTick();
	if(unsigned int pressed = nowPressed()){
		for(int i = 0; i < 15; ++i){
		    // If the button: Is pushed down && hasnt been pushed down last tick && is still in the cooldown period
			if(!((pressed>>i) & 1) || ((ispressed->buttons>>i) & 1) || timeouts[i] + starts[i] < Timer::GetFPGATimestamp()*1.0e3)
				continue;
			
			// The call it!
			call(presses[i]);
			
			// And prepare for the next tick
			ispressed->buttons &= 1<<i;
			needtotimeout[i] = true;
			starts[i] = Timer::GetFPGATimestamp() * 1.0e3; // Convert from nanoseconds to milliseconds
		}
	}
	// Check to see if we need to call anything on a release
	if(unsigned int unpressed = nowUnPressed()){
		for(int i = 0; i < 15; ++i){
			// If the button: was pushed && is no longer pressed then do do stuff
			if(!((unpressed>>i) & 1))
				continue;
			call(releases[i]);
		}
	}

	// Check to see if we need to call anything on a timeout
	for(int i = 0; i < 15; ++i){
		if(timeoutcalls[i] != NULL && needtotimeout[i] && timeouts[i] + starts[i] < Timer::GetFPGATimestamp()*1.0e3){
			call(timeoutcalls[i]);
			needtotimeout[i] = false;
		}
	}
}

void Operator::updateDriveSystem(){
	jsBaseTickAxis();
	if(axis->trigger < -0.5){
		;// Pass ball
	} else if (axis->trigger > 0.5){
		; // ShootBall
	}
	
	//
	// Meccanum Stuff!
	//
	
	//
	// Arm tilt level
	//
}

void Operator::call(void (*function)()){
	if(function != NULL){
		(*function)();
	}
}








