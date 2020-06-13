#ifndef BooleanParameterField_h
#define BooleanParameterField_h

#include "ParameterField.h"

class BooleanParameterField : public ParameterField {

public:
    BooleanParameterField(const char* _name);
    void increment(int amount);
    void decrement(int amount);
    void render(Display& display, uint8_t row, bool selected);

    void setValue(bool _value) { value = _value; }
    bool getValue() { return value; }

private:
    bool value;

};


#endif
