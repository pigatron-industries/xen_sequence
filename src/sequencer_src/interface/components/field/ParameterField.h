#ifndef ParameterField_h
#define ParameterField_h

#include "lib/drivers/Display.h"

#define FIELD_HEIGHT 11
#define TEXT_HEIGHT 7
#define FIELD_NAME_WIDTH 45
#define FIELD_VALUE_WIDTH 45

class ParameterField {

public:
    ParameterField(const char* _name);
    virtual void increment(int16_t amount) = 0;
    virtual void decrement(int16_t amount) = 0;
    virtual void render(Display& display, uint8_t row);

    void setEnabled(bool _enabled) { enabled = _enabled; dirtyLabel = true; dirtyValue = true; }
    void setSelected(bool _selected) { selected = _selected; dirtyValue = true; }
    void setDirty() { dirtyLabel = true; dirtyValue = true; }

protected:
    const char* name;
    bool enabled = true;
    bool selected = false;
    bool dirtyLabel = true;
    bool dirtyValue = true;

};


#endif