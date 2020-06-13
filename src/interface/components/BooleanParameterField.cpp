#include "BooleanParameterField.h"

BooleanParameterField::BooleanParameterField(const char* _name) :
    ParameterField(_name)
     {
}

void BooleanParameterField::increment(int16_t amount) {
    value = !value;
}

void BooleanParameterField::decrement(int16_t amount) {
    value = !value;
}

void BooleanParameterField::render(Display& display, uint8_t row) {
    if(enabled) {
        ParameterField::render(display, row);
        display.print(value ? "ON" : "OFF");
    }
}
