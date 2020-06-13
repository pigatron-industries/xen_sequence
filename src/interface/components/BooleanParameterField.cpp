#include "BooleanParameterField.h"

BooleanParameterField::BooleanParameterField(const char* _name) :
    ParameterField(_name)
     {
}

void BooleanParameterField::increment(int amount) {
    value = !value;
}

void BooleanParameterField::decrement(int amount) {
    value = !value;
}

void BooleanParameterField::render(Display& display, uint8_t row, bool selected) {
    if(enabled) {
        ParameterField::render(display, row, selected);
        display.print(value ? "ON" : "OFF");
    }
}
