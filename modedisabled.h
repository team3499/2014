#ifndef MODEDISABLED_H
#define MODEDISABLED_H

#include "modebase.h"

class ModeDisabled : public ModeBase {
public:
    ModeDisabled(DriverStation *ds);
    ~ModeDisabled();
    
    void begin();
    void run();
    void end();
};

#endif // MODEDISABLED_H
