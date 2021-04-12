#include "ParameterField.h"
#include "lib/util/debug.h"

ParameterField::SelectMode ParameterField::selectMode = SelectMode::FIELD;

ParameterField::ParameterField(const char* _name) :
    name(_name) {
    height = FIELD_HEIGHT;
    width = FIELD_WIDTH;
    setFocusable(true);
}

void ParameterField::render(GraphicsContext& g) {
    DEBUG("ParameterField::render")
    Component::render(g);
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
        Hardware::display.fillRect(FIELD_NAME_WIDTH-2, g.yPos, FIELD_VALUE_WIDTH+2, height, Colour::BLACK);
        if(selected) {
            Hardware::display.drawRect(FIELD_NAME_WIDTH-2, g.yPos, FIELD_VALUE_WIDTH+2, height, selectMode == SelectMode::FIELD ? SELECTED_COLOUR : VALUE_COLOUR);
            Hardware::display.setTextColour(selectMode == SelectMode::FIELD ? VALUE_COLOUR : SELECTED_COLOUR);
        } else {
            Hardware::display.setTextColour(VALUE_COLOUR);
        }
    }

    Hardware::display.setCursor(FIELD_NAME_WIDTH, g.yPos+TEXT_HEIGHT);
}

void ParameterField::changeSelectMode() {
    ParameterField::selectMode = ParameterField::selectMode == ParameterField::SelectMode::FIELD ? ParameterField::SelectMode::VALUE : ParameterField::SelectMode::FIELD;
    dirtyValue = true;
    if(listener != NULL) {
        listener->onSelectModeChange(this);
    }
}