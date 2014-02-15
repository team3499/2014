#include "modebase.h"

class ModeAutonomous : public ModeBase {
public:
	ModeAutonomous();
	~ModeAutonomous();
	
	void start();
	void run();
	void end();
};
