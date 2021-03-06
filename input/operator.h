#ifndef OPERATOR_H
#define OPERATOR_H

#include <Timer.h>

#include "input/jsbase.h"


class Operator : public JsBase {
public:
    Operator();

    void regAction(unsigned int button, void (*press)(), void (*release)(), void (*time)(), unsigned int timeout);

    void unregAction(unsigned int button);
    
//    void update();
//    void updateDriveSystem();
    
private:
    
    void call(void (*function)());
    
    void (**presses)();
    void (**releases)();
    void (**timeoutcalls)();
    unsigned int *timeouts;
    unsigned int *starts;
    bool *needtotimeout;
    
    JsBase::JsButtons *ispressed;
};

#endif // OPERATOR_H
