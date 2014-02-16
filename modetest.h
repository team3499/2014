#ifndef MODETEST_H
#define MODETEST_H

#include "modebase.h"

#include <fstream>

class ModeTest : public ModeBase {
public:
	ModeTest(DriverStation *ds);
	~ModeTest();
	
	void init();
	void run();
	void end();
private:
	int test_mode;
	std::ofstream *jaglog;
};

#endif
