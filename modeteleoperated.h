#ifndef MODETELEOPERATED_H
#define MODETELEOPERATED_H

#include "modebase.h"

#include <fstream>

#define abs(x) (x < 0 ? -x : x)

class ModeTeleoperated : public ModeBase {
public:
	ModeTeleoperated(DriverStation *ds);
	~ModeTeleoperated();
	
	void init();
	void run();
	void end();
private:
	bool use_proximity;
	std::ofstream *jaglog;
};

#endif
