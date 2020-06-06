#ifndef ParameterField_h
#define ParameterField_h

#include "../../lib/drivers/Display.h"

#define FIELD_HEIGHT 11
#define TEXT_HEIGHT 7
#define FIELD_NAME_WIDTH 45
#define FIELD_VALUE_WIDTH 45

class ParameterField {

public:
    ParameterField(const char* _name);
    virtual void increment() = 0;
    virtual void decrement() = 0;
    virtual void render(Display& display, uint8_t row, bool selected) = 0;

protected:
    const char* name;

};


#endif
