#include "outputcommon.h"

class ModeBase : public OutputCommon {
public:
	ModeBase();
	~ModeBase();
	
	virtual void start();
	virtual void run();
	virtual void end();
};
