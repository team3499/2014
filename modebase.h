#ifndef MODEBASE_H
#define MODEBASE_H

#include "outputcommon.h"

class ModeBase : public OutputCommon {
public:
    ModeBase(DriverStation *ds);
    virtual ~ModeBase();
    
    void start();
    void stop();
    
    virtual void begin();
    virtual void run();
    virtual void end();
    
    virtual const char *typeString();
private:
    bool isrun;
protected:
    DriverStation *m_ds;
};

#endif // MODEBASE_H
