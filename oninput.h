#ifndef ONINPUT_H
#define ONINPUT_H

class OnInput
{
public:
    OnInput();

    // Returns ID that the call was registered to.
    int regCall( void (*function)(), unsigned int timeout,  );

    unsigned int callCount();

    void (**calls)();

    void storefunc(){
        void (*funcpt)() = &func;
    }

    // An array of timeouts for preventing double-triggers
    unsigned int *timeout;
};

#endif // ONINPUT_H
