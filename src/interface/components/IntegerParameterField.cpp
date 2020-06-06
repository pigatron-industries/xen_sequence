#include "IntegerParameterField.h"

IntegerParameterField::IntegerParameterField(const char* _name, uint16_t _value, uint16_t _min, uint16_t _max, const char* _unit) :
    ParameterField(_name),
    value(_value),
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
    uint8_t top = row*FIELD_HEIGHT;

    display.setTextColour(Colour(0, 128, 255));
    display.setCursor(0, top+TEXT_HEIGHT);
    display.print(name);

    if(selected) {
        display.fillRect(FIELD_NAME_WIDTH-2, top+1, FIELD_VALUE_WIDTH, TEXT_HEIGHT+2, Colour(255, 255, 0));
        display.setTextColour(Colour(0, 0, 0));
    } else {
        display.setTextColour(Colour(255, 255, 0));
    }

    display.setCursor(FIELD_NAME_WIDTH, top+TEXT_HEIGHT);
    display.print(value);
    display.print(unit);
}
