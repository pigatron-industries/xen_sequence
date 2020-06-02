#ifndef InputTask_h
#define InputTask_h

#include <inttypes.h>

#include "../lib/task/Task.h"
#include "InterfaceController.h"
#include "../lib/drivers/AnalogStick.h"


class InputTask : public Task {

public:
    InputTask(InterfaceController& _interface, uint8_t _stickXPin, uint8_t _stickYPin);
    void init();
    void execute();

private:
    InterfaceController& interface;

    AnalogStick analogStick;

};

#endif
