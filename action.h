#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
    Action();
    ~Action();

    void regCall( void (*function)(), unsigned int timeout,  void (*afterTimeout)() = NULL);

    unsigned int callCount();

    void activate();

private:
    void (**calls)();
    void (**afters)();
    unsigned int count;

    // An array of timeouts for preventing double-triggers
    unsigned int *timeout;
};

#endif // ACTION_H
