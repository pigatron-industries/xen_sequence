#include "BooleanParameterField.h"

BooleanParameterField::BooleanParameterField(const char* _name) :
    ParameterField(_name) {
}

void BooleanParameterField::increment(int16_t amount) {
    value = !value;
}

void BooleanParameterField::decrement(int16_t amount) {
    value = !value;
}

void BooleanParameterField::render(GraphicsContext& g) {
    if(enabled) {
        ParameterField::render(g);
        Hardware::display.print(value ? "ON" : "OFF");
    }
}
