#ifndef DRIVESYS_H
#define DRIVESYS_H

#include "const.h"
#include "input/operator.h"
#include "jaglog.h"

#include <CANJaguar.h>

class DriveSys {
public:
	typedef struct JagSpeed {
		float fl;
		float fr;
		float rl;
		float rr;
	};
	
	DriveSys(Operator *op);
	~DriveSys();
	
	void checkDead();
	
	void setLogging(bool logEh);
	bool loggingEh();  bool isLogging();
	
	void vroomvrum(); /* AKA drive */                                                                    																				                    	  void drive();
	void tchunk();    /* AKA stop  */                                                                                  																				              void stop();
	
	void setPID(double p, double i, double d);

	void setSpeeds(float fl, float fr, float rl, float rr);
	
	bool isNotDead(){
		return notdead;
	}
	
private:
	void setOutputs();
	
	bool ableToLog; // basically if we opened the file ok
	bool logEh;     // what we want to be doing
	
	CANJaguar *fr, *fl, *rl, *rr;
	JagLog *lg;
	
	Operator *op; // This should be a pointer to __THE__ operator instance
	JsBase::JsAxis *axii;
	
	bool notdead;
	
	JagSpeed *set;
	JagSpeed *oset;
	// JagSpeed *eset, *eset2;
};


#endif // DRIVESYS_H
