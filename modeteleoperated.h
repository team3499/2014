#include "modebase.h"

#define abs(x) (x < 0 ? -x : x)

class ModeTeleoperated : public ModeBase {
public:
	ModeTeleoperated();
	~ModeTeleoperated();
	
	void start();
	void run();
	void end();
private:
	bool use_proximity;
};
