#ifndef MODETEST_H
#define MODETEST_H

#include "modebase.h"

#include <fstream>

class ModeTest : public ModeBase {
public:
	ModeTest(DriverStation *ds);
	~ModeTest();
	
	void begin();
	void run();
	void end();
	
	const char *typeString();
private:
	int test_mode;
	std::ofstream *jaglog;
};

#endif
