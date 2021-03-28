#include "ParameterField.h"
#include "lib/util/debug.h"

ParameterField::SelectMode ParameterField::selectMode = SelectMode::FIELD;

ParameterField::ParameterField(const char* _name) :
    name(_name) {
    height = FIELD_HEIGHT;
    width = FIELD_WIDTH;
}

void ParameterField::render(GraphicsContext& g) {
    if(!visible) {
        return;
    }

    if(dirtyLabel || g.full) {
        Hardware::display.setTextColour(Colour(0, 128, 255));
        Hardware::display.setCursor(0, g.yPos+TEXT_HEIGHT);
        Hardware::display.print(name);
        dirtyLabel = false;
    }

    if(dirtyValue || g.full) {
        if(selected) {
            Hardware::display.fillRect(FIELD_NAME_WIDTH-2, g.yPos+1, FIELD_VALUE_WIDTH, TEXT_HEIGHT+2, selectMode == SelectMode::FIELD ? Colour::RED : Colour::YELLOW);
            Hardware::display.setTextColour(selectMode == SelectMode::FIELD ? Colour::BLACK : Colour::DARK_RED);
        } else {
            Hardware::display.fillRect(FIELD_NAME_WIDTH-2, g.yPos+1, FIELD_VALUE_WIDTH, TEXT_HEIGHT+2, Colour::BLACK);
            Hardware::display.setTextColour(Colour::YELLOW);
        }
    }

    Hardware::display.setCursor(FIELD_NAME_WIDTH, g.yPos+TEXT_HEIGHT);
}

void ParameterField::setSelectMode(SelectMode selectMode) {
    ParameterField::selectMode = selectMode;
    dirtyValue = true;
}