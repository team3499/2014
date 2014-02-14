#ifndef ACTION_H
#define ACTION_H

#include <stdlib.h>
#include <Utility.h>

class Action
{
public:
    Action();
    ~Action();

    // NOTE: timeout does TWO things; it is the time before executing afterTimeout, AND the time before you are able to activate the action again.
    // Other NOTE: Timeout is in MILLIseonds
    void regCall( void (*function)(), unsigned int timeout = 0,  void (*afterTimeout)() = NULL);

    unsigned int callCount();

    void activate();

private:
    void (**calls)();
    void (**afters)();
    unsigned int count;

    // An array of timeouts for preventing double-triggers
    // This is in milliseconds
    unsigned int *timeout;
    unsigned int lastCall; // MILLIseconds
};

#endif // ACTION_H