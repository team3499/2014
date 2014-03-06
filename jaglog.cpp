#include "jaglog.h"

JagLog::JagLog(const char *loglabel){
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

//    std::string sd_label = SD_GS("JAGLOG_LABEL_OVERRIDE");
//    if(!sd_label.empty())
//        label += sd_label;

    std::string name = "/jaglog/JAG_SPEED_";
    char str[6];
    sprintf(str, "%d", runCount);
    name += label;
    name += "_";
    name += str;
    name += ".log";

//        char wrt[256];
//        sprintf("JagLog file: \"%s\"\n", name.c_str());
//        VOUT(wrt);
    
    VOUT(name.c_str());
    
    jaglog.open(name.c_str());
    
    if(jaglog.bad()){
        OUT("!! OPENING OF THE JAGUAR LOGGING FILE FAILED!");
        logEh = false;
    } else {
        logEh = true;
    }
}
JagLog::~JagLog(){
    jaglog.close();
}

bool JagLog::canLog(){
    return logEh;
}

void JagLog::logDrive(double frset, double fr, double flset, double fl, double rrset, double rr, double rlset, double rl){
    if(logEh){
        jaglog << GetTime() << " " << frset << " " << fr << " " << flset << " " << fl << " " << rrset << " " << rr << " " << rlset << " " << rl << std::endl;
        jaglog.flush();
    }
}

void JagLog::logArm(double set, double current){
    if(logEh){
        jaglog << GetTime() << " " << set << " " << current << std::endl;
        jaglog.flush();
    }
}
