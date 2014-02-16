#ifndef MODEDISABLED_H
#define MODEDISABLED_H

#include "modebase.h"

class ModeDisabled : public ModeBase {
public:
	ModeDisabled(DriverStation *ds);
	~ModeDisabled();
	
	void init();
	void run();
	void end();
};

#endif
