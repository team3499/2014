#ifndef DRIVESYS_INCLUDED
#define DRIVESYS_INCLUDED

#include "../jaglog.h"
#include "../input/operator.h"

#include <CANJaguar.h>

class DriveSys {
public:
	DriveSys(Operator *op);
	~DriveSys();
	
	void setLogging(bool logEh);
	bool loggingEh();  bool isLogging();
	
	void vroomvrum(); /* AKA drive */                                                                                                void drive();
	void tchunk();    /* AKA stop  */                                                                                                void stop();
	
	void setPID(double p, double i, double d);

	void setOutputs(float fl, float fr, float rl, float rr);
private:
	
	bool ableToLog; // basically if we opened the file ok
	bool logEh;     // what we want to be doing
	
	CANJaguar *fr, *fl, *rl, *rr;
	JagLog *lg;
	
	Operator *op; // This should be a pointer to __THE__ operator instance
	JsBase::JsAxis *axii;
};


#endif /* #ifndef DRIVESYS_INCLUDED */
