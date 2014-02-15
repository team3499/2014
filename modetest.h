#include "modebase.h"

#include <fstream>

class ModeTest : public ModeBase {
public:
	ModeTest();
	~ModeTest();
	
	void start();
	void run();
	void end();
private:
	int test_mode;
	std::ofstream *jaglog;
};
