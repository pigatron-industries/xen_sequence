#ifndef InputTask_h
#define InputTask_h

#include <inttypes.h>

#include "lib/task/Task.h"
#include "InterfaceController.h"
#include "lib/drivers/Switch.h"
#include "lib/drivers/AnalogStick.h"
#include "lib/drivers/RotaryEncoder.h"
#include "Keypad.h"
#include "Keyboard.h"


class InputTask : public Task {

public:
    InputTask(InterfaceController& _interface);
    void init();
    void execute();

private:
    InterfaceController& interface;
    bool function = false;

    AnalogStick analogStick;
    Switch analogStickSwitch;
    RotaryEncoder encoder;
    Switch encoderSwitch;

};

#endif
