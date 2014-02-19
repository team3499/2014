#ifndef MODETEST_H
#define MODETEST_H

#include "modebase.h"
#include "jaglog.h"

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
	JagLog *jaglog;
	
	int arm_step;
	Timer *armtime;
	int arm_count;
	float armspeed;
};

#endif // MODETEST_H
