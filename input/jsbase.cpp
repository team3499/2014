#include "input/jsbase.h"

JsBase::JsBase(int jsport, JsBase::ControllerType type) {
	this->js = new Joystick(jsport);
	this->type = type;
	
	this->data = new JsButtons;
}

bool JsBase::getXBoxButton(JsBase::Button b){
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
    	return getButton(5);
    	break;
    case JsBase::BUTTON_BACK:
    	return getButton(6);
    	break;
    case JsBase::BUTTON_GUIDE:
    	return getButton(7);
    	break;
    case JsBase::BUTTON_RIGHTBUMPER:
    	return getButton(8);
    	break;
    case JsBase::BUTTON_LEFTBUMPER:
    	return getButton(9);
    	break;
    case JsBase::BUTTON_RIGHTJS:
    	return getButton(10);
    	break;
    case JsBase::BUTTON_LEFTJS:
    	return getButton(11);
    	break;
    case JsBase::BUTTON_DPAD_UP:
    	return getButton(12);
    	break;
    case JsBase::BUTTON_DPAD_DOWN:
    	return getButton(13);
    	break;
    case JsBase::BUTTON_D_DPAD_LEFT:
    	return getButton(14);
    	break;
    case JsBase::BUTTON_D_DPAD_RIGHT:
    	return getButton(15);
    	break;
    default:
    	return 0;
    	break;
    }
}

bool JsBase::getLogitechButton(JsBase::Button b){
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
    	return getButton(5);
    	break;
    case JsBase::BUTTON_BACK:
    	return getButton(6);
    	break;
    case JsBase::BUTTON_GUIDE:
    	return getButton(7);
    	break;
    case JsBase::BUTTON_RIGHTBUMPER:
    	return getButton(8);
    	break;
    case JsBase::BUTTON_LEFTBUMPER:
    	return getButton(9);
    	break;
    case JsBase::BUTTON_RIGHTJS:
    	return getButton(10);
    	break;
    case JsBase::BUTTON_LEFTJS:
    	return getButton(11);
    	break;
    case JsBase::BUTTON_DPAD_UP:
    	return getButton(12);
    	break;
    case JsBase::BUTTON_DPAD_DOWN:
    	return getButton(13);
    	break;
    case JsBase::BUTTON_D_DPAD_LEFT:
    	return getButton(14);
    	break;
    case JsBase::BUTTON_D_DPAD_RIGHT:
    	return getButton(15);
    	break;
    default:
    	return 0;
    	break;
    }
}

bool JsBase::getButton(JsBase::Button b){
    if(this->type == JsBase::xBoxController){
    	return getXBoxButton(b);
    } else { // Assume its a logitech
    	return getLogitechButton(b);
    }
}

bool JsBase::getButton(unsigned int button){
    return (this->data->buttons >> button) & 1;
}


bool JsBase::hasChanged(){
	update();
	return (!!(data->buttons - lastdata->buttons));
}


// This returns TWO float values (in an array). index 0 is x, index 1 is y
float *JsBase::getStick(JsBase::Stick side){
	if(side == LeftStick){
		float *ret;
		ret[0] = this->js->GetRawAxis(1);
		ret[1] = this->js->GetRawAxis(2);
	    return ret;
	} else { // Assume its right
		float *ret;
		ret[0] = this->js->GetRawAxis(3);
		ret[1] = this->js->GetRawAxis(4);
	    return ret;
	}
}

void JsBase::update(){
	delete lastdata;
	lastdata = data;
	data = new JsButtons;
	if(type == JsBase::xBoxController){
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
	} else {
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
}

float JsBase::getTrigger(JsBase::Trigger side){
	if(side == LeftTrigger){
		return this->js->GetRawAxis(5);
	} else { // Assume its right
		return this->js->GetRawAxis(6);
	}
}
