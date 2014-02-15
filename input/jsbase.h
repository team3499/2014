#ifndef JSBASE_H
#define JSBASE_H

#include <Joystick.h>

class JsBase {
public:

    enum Button {
        BUTTON_A = 1, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_START, BUTTON_BACK, BUTTON_GUIDE, BUTTON_RIGHTBUMPER, BUTTON_LEFTBUMPER,
        BUTTON_RIGHTJS, BUTTON_LEFTJS, BUTTON_DPAD_UP, BUTTON_DPAD_DOWN, BUTTON_D_DPAD_LEFT, BUTTON_D_DPAD_RIGHT
    };
    enum Stick {
        LeftStick, RightStick, DPad
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
    
    struct JsAxis {
    	float trigger;
    	union {
    		struct {
    			float x;
    			float y;
    		} rightStick;
    		struct {
    			float rs_x;
    			float rs_y;
    		};
    	};
    	union {
    		struct {
    			float x;
    			float y;
    		} leftStick;
    		struct {
    			float ls_x;
    			float ls_y;
    		};
    	};
    };

public:
    JsBase();

    bool getButton(JsBase::Button b);
    
    void jsBaseTick();
    void jsBaseTickAxis();
    bool hasChanged();

    float *getStick(JsBase::Stick);
    float getTrigger();
    
    unsigned int getRawInt();
    
    JsBase::JsAxis *getAxisInstance();
    
    JsBase::JsAxis *axis;
    
    unsigned int nowPressed();    
    unsigned int nowUnPressed();
    
private:
    static bool initialized;
    
    bool getButton(unsigned int button);

    Joystick *js;
    
    JsBase::JsButtons *data;
    JsBase::JsButtons *lastdata;
};

#endif // JSBASE_H
