#include "drivesys.h"

DriveSys::DriveSys(Operator *op){
	this->op = op;
	this->axii = this->op->getAxisInstance();
	
	lg = new JagLog("");
	ableToLog = lg->canLog();
	
	fl = new CANJaguar(5, CANJaguar::kSpeed);
	fr = new CANJaguar(2, CANJaguar::kSpeed);
	rl = new CANJaguar(4, CANJaguar::kSpeed);
	rr = new CANJaguar(3, CANJaguar::kSpeed);
	
    fl->SetExpiration(0.1);
    fr->SetExpiration(0.1);
    rl->SetExpiration(0.1);
    rr->SetExpiration(0.1);

    fl->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
    fr->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
    rl->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
    rr->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

    fl->ConfigEncoderCodesPerRev(1024);
    fr->ConfigEncoderCodesPerRev(1024);
    rl->ConfigEncoderCodesPerRev(1024);
    rr->ConfigEncoderCodesPerRev(1024);

    fl->SetPID(0.200, 0.001, 0.000);
    fr->SetPID(0.200, 0.001, 0.000);
    rl->SetPID(0.200, 0.001, 0.000);
    rr->SetPID(0.200, 0.001, 0.000);

    fl->EnableControl();
    fr->EnableControl();
    rl->EnableControl();
    rr->EnableControl();
}

DriveSys::~DriveSys(){
	delete fl;
	delete fr;
	delete rl;
	delete rr;
}

void DriveSys::setLogging(bool logEh){
	this->logEh = ableToLog * logEh;
}
bool DriveSys::loggingEh(){
	return ableToLog * logEh;
}
bool DriveSys::isLogging(){
	return ableToLog * logEh;
}

void DriveSys::vroomvrum(){
	op->jsBaseTick();
	op->jsBaseTickAxis();

	float jx = axii->leftStick.x;
	float jy = axii->leftStick.y;
	float dx = axii->dpad_x * .707;
	float dy = axii->dpad_y * .707;

	float fr = jy - jx - dx + dy;
	float fl = jy + jx + dx + dy;
	float rr = jy - jx + dx + dy;
	float rl = jy + jx - dx + dy;

	float mx = maxf( 1.000, maxf(maxf(fr, fl), maxf(rr, rl)));

	fr /= mx;
	fl /= mx;
	rr /= mx;
	rl /= mx;

	fr = fr * fr * (fr > 0 ? 1 : -1);
	fl = fl * fl * (fl > 0 ? 1 : -1);
	rr = rr * rr * (rr > 0 ? 1 : -1);
	rl = rl * rl * (rl > 0 ? 1 : -1);

	fr *= 400; // multiply by wheel constant
	fl *= 400; // multiply by wheel constant
	rr *= 400; // multiply by wheel constant
	rl *= 400; // multiply by wheel constant

	fr = (absf(fr) > 30 ? fr : 0.0);
	fl = (absf(fl) > 30 ? fl : 0.0);
	rr = (absf(rr) > 30 ? rr : 0.0);
	rl = (absf(rl) > 30 ? rl : 0.0);

	this->fr->Set(-fr);
	this->fl->Set( fl);
	this->rr->Set(-rr);
	this->rl->Set( rl);

	if(logEh && ableToLog)
        lg->logDrive(fr, this->fr->GetSpeed(), fl, this->fl->GetSpeed(), rr, this->rr->GetSpeed(), rl, this->rl->GetSpeed());
}

void DriveSys::drive(){
	vroomvrum();
}

void DriveSys::tchunk(){
	setOutputs(0.0, 0.0, 0.0, 0.0);
}

void DriveSys::stop(){
	tchunk();
}

void DriveSys::setOutputs(float fl, float fr, float rl, float rr){
	this->fl->Set(fl);
	this->fr->Set(fr);
	this->rl->Set(rl);
	this->rr->Set(rr);
}