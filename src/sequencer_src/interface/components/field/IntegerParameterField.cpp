#include "IntegerParameterField.h"

IntegerParameterField::IntegerParameterField(const char* _name, int16_t _min, int16_t _max, const char* _unit) :
    ParameterField(_name),
    min(_min),
    max(_max),
    unit(_unit)
     {
}

void IntegerParameterField::increment(int16_t amount) {
    value += amount;
    if(value > max) {
        value = max;
    }
    dirtyValue = true;
}

void IntegerParameterField::decrement(int16_t amount) {
    value -= amount;
    if(value < min) {
        value = min;
    }
    dirtyValue = true;
}

void IntegerParameterField::render(GraphicsContext& g) { 
    if(visible) {
        ParameterField::render(g);
        if(dirtyValue || g.full) {
            Hardware::display.print(value);
            Hardware::display.print(unit);
            dirtyValue = false;
        }
    }
}
