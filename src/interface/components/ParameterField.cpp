#include "ParameterField.h"

ParameterField::ParameterField(const char* _name) :
    name(_name) {
}

void ParameterField::render(Display& display, uint8_t row) {
    uint8_t top = row*FIELD_HEIGHT;

    if(dirtyLabel) {
        display.setTextColour(Colour(0, 128, 255));
        display.setCursor(0, top+TEXT_HEIGHT);
        display.print(name);
        dirtyLabel = false;
    }

    if(dirtyValue) {
        if(selected) {
            display.fillRect(FIELD_NAME_WIDTH-2, top+1, FIELD_VALUE_WIDTH, TEXT_HEIGHT+2, Colour(255, 255, 0));
            display.setTextColour(Colour(0, 0, 0));
        } else {
            display.fillRect(FIELD_NAME_WIDTH-2, top+1, FIELD_VALUE_WIDTH, TEXT_HEIGHT+2, Colour(0, 0, 0));
            display.setTextColour(Colour(255, 255, 0));
        }
    }

    display.setCursor(FIELD_NAME_WIDTH, top+TEXT_HEIGHT);
}
