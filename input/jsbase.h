#ifndef JSBASE_H
#define JSBASE_H

#include <Joystick.h>

class JsBase
{
public:

	enum ControllerType {
		xBoxController = 1, LogitechController
	};
	enum Button {
		BUTTON_A = 1, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_START, BUTTON_BACK, BUTTON_GUIDE, BUTTON_RIGHTBUMPER, BUTTON_LEFTBUMPER,
		BUTTON_RIGHTJS, BUTTON_LEFTJS, BUTTON_DPAD_UP, BUTTON_DPAD_DOWN, BUTTON_D_DPAD_LEFT, BUTTON_D_DPAD_RIGHT
	};
	enum Stick {
		LeftStick, RightStick
	};
	enum Trigger {
		LeftTrigger, RightTrigger
	};

	struct JsButtons {
		union {
			struct {
				unsigned button16 : 1;
				unsigned button15 : 1;
				unsigned button14 : 1;
				unsigned button13 : 1;
				unsigned button12 : 1;
				unsigned button11 : 1;
				unsigned button10 : 1;
				unsigned button9  : 1;

				unsigned button8  : 1;
				unsigned button7  : 1;
				unsigned button6  : 1;
				unsigned button5  : 1;
				unsigned button4  : 1;
				unsigned button3  : 1;
				unsigned button2  : 1;
				unsigned button1  : 1;
			};
			short buttons;
		};

	};

public:
	JsBase(int jsport, JsBase::ControllerType type);

	bool getButton(JsBase::Button b);
	
	void update();
	bool hasChanged();

	float *getStick(JsBase::Stick);
	float getTrigger(JsBase::Trigger);
	
private:
	bool getXBoxButton(JsBase::Button b);
	bool getLogitechButton(JsBase::Button b);
	
	bool getButton(unsigned int button);

	JsBase::ControllerType type;

	Joystick *js;
	
	JsBase::JsButtons *data;
	JsBase::JsButtons *lastdata;
};

#endif // JSBASE_H
