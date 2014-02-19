#ifndef MODETELEOPERATED_H
#define MODETELEOPERATED_H

#include "modebase.h"
#include "input/jsbase.h"
#include "tcpconnection.h"
#include "jaglog.h"

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
	JsBase::JsAxis *axii;
	JsBase::JsButtons *btns;
	
	bool lockarms;
};

#endif // MODETELEOPERATED_H
