#include "PitchParameterField.h"

PitchParameterField::PitchParameterField(const char* _name) :
    ParameterField(_name) {
}

void PitchParameterField::increment(int16_t amount) {
    value += amount;
    if(value > max) {
        value = max;
    }
    dirtyValue = true;
}

void PitchParameterField::decrement(int16_t amount) {
    value -= amount;
    if(value < min) {
        value = min;
    }
    dirtyValue = true;
}

void PitchParameterField::render(Display& display, uint8_t row) {
    if(enabled) {
        ParameterField::render(display, row);
        if(dirtyValue) {
            display.print(noteNames[value]);
            dirtyValue = false;
        }
    }
} 
