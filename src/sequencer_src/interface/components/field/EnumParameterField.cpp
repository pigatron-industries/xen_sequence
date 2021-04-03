#include "EnumParameterField.h"

EnumParameterField::EnumParameterField(const char* _name, const char** names, int8_t size) :
    ParameterField(_name) {
         this->names = names;
         this->size = size;
}

void EnumParameterField::increment(int16_t amount) {
    value += amount;
    if(value >= size) {
        value = size-1;
    }
    dirtyValue = true;
}

void EnumParameterField::decrement(int16_t amount) {
    value -= amount;
    if(value < 0) {
        value = 0;
    }
    dirtyValue = true;
}

void EnumParameterField::render(GraphicsContext& g) { 
    if(visible) {
        ParameterField::render(g);
        if(dirtyValue || g.full) {
            Hardware::display.print(names[value]);
            dirtyValue = false;
        }
    }
}
