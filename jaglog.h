#ifndef JAGLOG_H
#define JAGLOG_H

#include "const.h"

#include <fstream>
#include <Timer.h>

class JagLog {
public:
    JagLog(const char *loglabel);
    ~JagLog();
    
    bool canLog();
    
    void logDrive(double frset, double fr, double flset, double fl, double rrset, double rr, double rlset, double rl);
    void logArm(double set, double current);
private:
    std::ofstream jaglog;
    bool logEh;
};

#endif // JAGLOG_H
