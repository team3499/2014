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
    this->timeout[count] = timeout;
    afters[count] = afterTimeout; // This doesnt matter if its null or not.
    ++count;
}

unsigned int Action::callCount(){
    return count;
}

void Action::activate(){
    for(unsigned int i = 0; i < count; i++){
        (*(calls[count]))();

        if(afters[count]){
            // Schedule an event timeout msec from now.
            // Schedule::addSingle(this, count, timeout[count]);
        }
    }
}
