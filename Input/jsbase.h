#ifndef JSBASE_H
#define JSBASE_H

class JsBase
{
public:
    // to whoever reads this: yea, it works.
    enum class ControllerType : char {
        xBoxController, LogitechController, NonController
    };
    enum class Button : char {
        BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_START, BUTTON_BACK, BUTTON_GUIDE, BUTTON_RIGHTBUMPER, BUTTON_LEFTBUMPER,
        BUTTON_RIGHTJS, BUTTON_LEFTJS, BUTTON_DPAD_UP, BUTTON_DPAD_DOWN, BUTTON_D_DPAD_LEFT, BUTTON_D_DPAD_RIGHT
    };

    struct JsButtons {
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

public:
    JsBase();

    static inline bool getXBoxButton();
    static inline bool getLogitechButton(unsigned short joystickdata, );
    static inline bool getButton(unsigned short joystickdata, JsBase::Button b, JsBase::ControllerType c);

private:
    static inline bool getButton(unsigned short joystickdata, unsigned int button){
        return (joystickdata >> button) & 1;
    }

    unsigned short joystick;
};

#endif // JSBASE_H
