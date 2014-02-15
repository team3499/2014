#include "jsbase.h"

JsBase::JsBase() {
	if(!initialized){
        this->js = new Joystick(1);
        JsBase::initialized = true;
	} else {
		printf("THERE IS A MISUSE OF CODE! SOMEONE INITIALIZED ANOTHER INSTANCE OF JSBASE\n");
		return;
	}
    
	this->axis = new JsBase::JsAxis;
	
    this->data = new JsButtons;
    this->lastdata = new JsButtons;
}

bool JsBase::getButton(JsBase::Button b){
    switch(b){
    case JsBase::BUTTON_A:
        return getButton(1);
        break;
    case JsBase::BUTTON_B:
        return getButton(2);
        break;
    case JsBase::BUTTON_X:
        return getButton(3);
        break;
    case JsBase::BUTTON_Y:
        return getButton(4);
        break;
    case JsBase::BUTTON_START:
        return getButton(8);
        break;
    case JsBase::BUTTON_BACK:
        return getButton(7);
        break;
    case JsBase::BUTTON_RIGHTBUMPER:
        return getButton(6);
        break;
    case JsBase::BUTTON_LEFTBUMPER:
        return getButton(5);
        break;
    case JsBase::BUTTON_RIGHTJS:
        return getButton(10);
        break;
    case JsBase::BUTTON_LEFTJS:
        return getButton(9);
        break;
    case JsBase::BUTTON_DPAD_UP:
    	return getStick(DPad)[1] > 0.5;
        break;
    case JsBase::BUTTON_DPAD_DOWN:
    	return getStick(DPad)[1] < -0.5;
        break;
    case JsBase::BUTTON_D_DPAD_LEFT:
    	return getStick(DPad)[0] < -0.5;
        break;
    case JsBase::BUTTON_D_DPAD_RIGHT:
    	return getStick(DPad)[0] > 0.5;
        break;
    default:
        return 0;
        break;
    }
}

bool JsBase::getButton(unsigned int button){
    return (this->data->buttons >> button) & 1;
}


bool JsBase::hasChanged(){
    jsBaseTick();
    return (!!(data->buttons - lastdata->buttons));
}


// This returns a POINTER to MEMORY THAT GETS UPDATED (maybe). DO NOT SET OR DELETE!
JsBase::JsAxis *JsBase::getAxisInstance(){
	return this->axis;
}

void JsBase::jsBaseTick(){
    delete lastdata;
    lastdata = data;
    data = new JsButtons;
    data->button1  = js->GetRawButton(1);
    data->button2  = js->GetRawButton(2);
    data->button3  = js->GetRawButton(3);
    data->button4  = js->GetRawButton(4);
    data->button5  = js->GetRawButton(5);
    data->button6  = js->GetRawButton(6);
    data->button7  = js->GetRawButton(7);
    data->button8  = js->GetRawButton(8);
    data->button9  = js->GetRawButton(9);
    data->button10 = js->GetRawButton(10);
    data->button11 = js->GetRawButton(11);
    data->button12 = js->GetRawButton(12);
    data->button13 = js->GetRawButton(13);
    data->button14 = js->GetRawButton(14);
    data->button15 = js->GetRawButton(15);
}

void JsBase::jsBaseTickAxis(){
	axis->trigger = getTrigger();
	
	axis->ls_x = js->GetRawAxis(1);
	axis->ls_y = js->GetRawAxis(2);
	
	axis->rs_x = js->GetRawAxis(4);
	axis->rs_y = js->GetRawAxis(5);
}

// This assumes the RIGHT trigger is positive
float JsBase::getTrigger(){
    return -this->js->GetRawAxis(3);
}

unsigned int JsBase::getRawInt(){
	return data->buttons;
}


unsigned int JsBase::nowPressed(){
	// AKA: what wasn't pressed, AND what is now pressed
	return ((~lastdata->buttons) & data->buttons);
}

unsigned int JsBase::nowUnPressed(){
	// AKA: what was pressed, AND what is not pressed
	return ((lastdata->buttons) & ~(data->buttons));
}


