#ifndef JAGLOG_H
#define JAGLOG_H

#include "outputcommon.h"


#ifndef SD_PN
  #define SD_PN(n, x) SmartDashboard::PutNumber(n, x)
  #define SD_GN(n)    SmartDashboard::GetNumber(n)

  #define SD_PB(n, x) SmartDashboard::PutBoolean(n, x)
  #define SD_GB(n)    SmartDashboard::GetBoolean(n)

  #define SD_PS(n, x) SmartDashboard::PutString(n, x)
  #define SD_GS(n)    SmartDashboard::GetString(n)

  #define OUT(A) printf("$$FRC3499$$ - " A "\n"); fflush(stdout)
  #define VOUT(A) printf("$$FRC3499$$ - %s\n", A); fflush(stdout)
#endif


#include <fstream>
#include <Timer.h>

class JagLog {
public:
	JagLog(const char *loglabel){
		std::string label = loglabel;
	    int runCount = 9000;

	    FILE *file = fopen("/jaglog/jaglog_counter", "r");
	    if(file == NULL){
	    	OUT("Could not read /jaglog/jaglog_counter");
	    } else {
	        fscanf(file, "%d", &runCount);
	        fclose(file);
	    }

	    std::fstream *fileNumber = new std::fstream("/jaglog/jaglog_counter", std::ios_base::out | std::ios_base::trunc);
	    if(fileNumber == NULL){
	    	OUT("Could not write /jaglog/jaglog_counter");
	    } else {
	    	fileNumber->seekg(0, std::ios_base::beg);
	    	runCount++;
	    	*fileNumber << runCount;
	    	fileNumber->flush();
	    	delete fileNumber;
	    }

	    std::string sd_label = SD_GS("JAGLOG_LABEL_OVERRIDE");
	    if(!sd_label.empty())
	    	label += sd_label;

	    std::string name = "/jaglog/JAG_SPEED_";
	    char str[6];
	    sprintf(str, "%d", runCount);
	    name += label;
	    name += "_";
	    name += str;
	    name += ".log";

//	    char wrt[256];
//	    sprintf("JagLog file: \"%s\"\n", name.c_str());
//	    VOUT(wrt);
	    
	    VOUT(name.c_str());
	    
	    jaglog = new std::ofstream(name.c_str());
	    
	    if(jaglog->bad()){
	    	OUT("!! OPENING OF THE JAGUAR LOGGING FILE FAILED!");
	    	logEh = false;
	    } else {
	    	logEh = true;
	    }
	}
	~JagLog(){
		jaglog->close();
		delete jaglog;
	}
	
	void logDrive(double frset, double fr, double flset, double fl, double rrset, double rr, double rlset, double rl){
		if(logEh){
			*jaglog << GetTime() << " " << frset << " " << fr << " " << flset << " " << fl << " " << rrset << " " << rr << " " << rlset << " " << rl << std::endl;
			jaglog->flush();
		}
	}
	
	bool canLog(){
		return logEh;
    }
	
	void logArm(double set, double current){
		if(logEh){
			*jaglog << GetTime() << " " << set << " " << current << std::endl;
			jaglog->flush();
		}
	}
private:
	std::ofstream *jaglog;
	bool logEh;
};

#endif // JAGLOG_H
