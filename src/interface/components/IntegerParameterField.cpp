#include "IntegerParameterField.h"

IntegerParameterField::IntegerParameterField(const char* _name, uint16_t _value) :
    ParameterField(_name),
    value(_value) {
}

void IntegerParameterField::increment() {
    Serial.println("increment");
    value++;
}

void IntegerParameterField::decrement() {
    value--;
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
}
