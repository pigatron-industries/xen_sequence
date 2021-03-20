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

void PitchParameterField::render(GraphicsContext& g) {
    if(enabled) {
        ParameterField::render(g);
        if(dirtyValue) {
            Hardware::display.print(noteNames[value]);
            dirtyValue = false;
        }
    }
} 
