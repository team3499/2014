#ifndef MODETELEOPERATED_H
#define MODETELEOPERATED_H

#include "modebase.h"
#include "input/jsbase.h"
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
	bool holdlights;
	
	bool showlag;
	
	Timer shooter_timeout;
	bool timeout_started;
	float shooter_delay;
	
	bool openarms;
	bool shootball;
	bool passball;
};

#endif // MODETELEOPERATED_H
