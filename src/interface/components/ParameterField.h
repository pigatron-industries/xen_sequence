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
    virtual void increment(int amount) = 0;
    virtual void decrement(int amount) = 0;
    virtual void render(Display& display, uint8_t row, bool selected);

    void setEnabled(bool _enabled) { enabled = _enabled; }

protected:
    const char* name;
    bool enabled = true;

};


#endif
