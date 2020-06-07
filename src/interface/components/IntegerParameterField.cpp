#include "IntegerParameterField.h"

IntegerParameterField::IntegerParameterField(const char* _name, uint16_t _min, uint16_t _max, const char* _unit) :
    ParameterField(_name),
    min(_min),
    max(_max),
    unit(_unit)
     {
}

void IntegerParameterField::increment() {
    if(value < max) {
        value++;
    }
}

void IntegerParameterField::decrement() {
    if(value > min) {
        value--;
    }
}

void IntegerParameterField::render(Display& display, uint8_t row, bool selected) {
    if(enabled) {
        ParameterField::render(display, row, selected);
        display.print(value);
        display.print(unit);
    }
}
