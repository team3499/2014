#ifndef MODEAUTONOMOUS_H
#define MODEAUTONOMOUS_H

#include "modebase.h"

class ModeAutonomous : public ModeBase {
public:
	ModeAutonomous(DriverStation *ds);
	~ModeAutonomous();
	
	void init();
	void run();
	void end();
};

#endif
