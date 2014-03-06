#include "action.h"

Action::Action(){
    count = 0;
}

void Action::regCall( void (*function)(), unsigned int timeout,  void (*afterTimeout)()){
//    void (**calls)();
//    void (**afters)();

    // Check for special input (aka timeout == 0)
    if(timeout == 0 && afterTimeout)
        regCall(afterTimeout);

    calls[count] = function;
    this->timeouts[count] = timeout;
    afters[count] = afterTimeout; // This doesnt matter if its null or not.
    ++count;
}

unsigned int Action::callCount(){
    return count;
}

void Action::activate(){
    // GetFPGATime() returns microseconds, so convert to milliseconds.
    if((GetFPGATime() * 1.0e-3) <= (timeouts[count] + lastCall)){
        for(unsigned int i = 0; i < count; i++){
            (*(calls[count]))();

            if(afters[count]){
                // Schedule an event timeout msec from now.
                // Schedule::addSingle(this, count, timeout[count]);
            }
        }

        // Set the run time
        lastCall = GetFPGATime() * 1.0e-3;
    } // If we are too early, dont do anything.
}

//void Action::release(){
//    for(int i = 0; i < releaseCount); ++i){
//        (*(releases[i]))();
//    }
//}

void Action::update(){
    ;
}
