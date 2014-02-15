#include "modebase.h"

class ModeDisabled : public ModeBase {
public:
	ModeDisabled();
	~ModeDisabled();
	
	void start();
	void run();
	void end();
};
