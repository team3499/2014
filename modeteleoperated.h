#ifndef MODETELEOPERATED_H
#define MODETELEOPERATED_H

#include "modebase.h"

#include "input/jsbase.h"
#include "tcpconnection.h"

#include <fstream>

class ModeTeleoperated : public ModeBase {
public:
	ModeTeleoperated(DriverStation *ds);
	~ModeTeleoperated();
	
	void begin();
	void run();
	void end();
	
	const char *typeString();
private:
	
	std::ofstream *jaglog;
	bool logEh; // Should we log?
	
	JsBase::JsAxis *axii;
};

#endif
