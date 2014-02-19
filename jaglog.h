#ifndef JAGLOG_H
#define JAGLOG_H

#include "const.h"

#include <fstream>
#include <Timer.h>

//#ifndef SD_PN
//  #define SD_PN(n, x) SmartDashboard::PutNumber(n, x)
//  #define SD_GN(n)    SmartDashboard::GetNumber(n)
//
//  #define SD_PB(n, x) SmartDashboard::PutBoolean(n, x)
//  #define SD_GB(n)    SmartDashboard::GetBoolean(n)
//
//  #define SD_PS(n, x) SmartDashboard::PutString(n, x)
//  #define SD_GS(n)    SmartDashboard::GetString(n)
//
//  #define OUT(A) printf("$$FRC3499$$ - " A "\n"); fflush(stdout)
//  #define VOUT(A) printf("$$FRC3499$$ - %s\n", A); fflush(stdout)
//#endif

class JagLog {
public:
	JagLog(const char *loglabel);
	~JagLog();
	
	bool canLog();
	
	void logDrive(double frset, double fr, double flset, double fl, double rrset, double rr, double rlset, double rl);
	void logArm(double set, double current);
private:
	std::ofstream *jaglog;
	bool logEh;
};

#endif // JAGLOG_H
