#include "RangeParameterField.h"

RangeParameterField::RangeParameterField(const char* name, int16_t min, int16_t max) :
    ParameterField(name) {
        this->min = min;
        this->max = max;
        selectedValue = Value::NONE;
}

void RangeParameterField::setMinValue(int16_t minVvalue) { 
    this->minValue = minValue; 
    dirtyValue = true; 
}

void RangeParameterField::setMaxValue(int16_t maxValue) { 
    this->maxValue = maxValue; 
    if(this->maxValue <= minValue) {
        this->maxValue = minValue + 1;
    }
    dirtyValue = true; 
}

void RangeParameterField::increment(int16_t amount) {
    if(selectedValue == Value::MIN) {
        minValue += amount;
        if(minValue >= maxValue) {
            minValue = maxValue - 1;
        }
    } else {
        maxValue += amount;
        if(maxValue > max) {
            maxValue = max;
        }
    }
    dirtyValue = true;
}

void RangeParameterField::decrement(int16_t amount) {
    if(selectedValue == Value::MIN) {
        minValue -= amount;
        if(minValue < min) {
            minValue = min;
        }
    } else {
        maxValue -= amount;
        if(maxValue <= minValue) {
            maxValue = minValue + 1;
        }
    }
    dirtyValue = true;
}

void RangeParameterField::changeSelectMode() {
    if(ParameterField::selectMode == ParameterField::SelectMode::FIELD) {
        ParameterField::selectMode = ParameterField::SelectMode::VALUE;
        selectedValue = Value::MIN;
    } else if(ParameterField::selectMode == ParameterField::SelectMode::VALUE && selectedValue == Value::MIN) {
        selectedValue = Value::MAX;
    } else {
        ParameterField::selectMode = ParameterField::SelectMode::FIELD;
        selectedValue = Value::NONE;
    }
    dirtyValue = true;
}

void RangeParameterField::render(GraphicsContext& g) {
    if(visible) {
        ParameterField::render(g);
        if(dirtyValue || g.full) {

            //TODO calculate x positions properly
            int minPos = FIELD_NAME_WIDTH;
            int maxPos = FIELD_WIDTH;
            int minValuePos = FIELD_NAME_WIDTH+minValue;
            int maxValuePos = FIELD_NAME_WIDTH+maxValue;
            Hardware::display.fillRect(minValuePos, g.yPos+2, maxValuePos-minValuePos, height-4, Colour::YELLOW);
            Hardware::display.drawLine(minValuePos, g.yPos+2, minValuePos, g.yPos+height-3, valueColour(Value::MIN));
            Hardware::display.drawLine(maxValuePos, g.yPos+2, maxValuePos, g.yPos+height-3, valueColour(Value::MAX));

            // Hardware::display.setTextColour(valueColour(Value::MIN));
            // Hardware::display.print(minValue);
            // Hardware::display.setTextColour(Colour::BLACK);
            // Hardware::display.print(" - ");
            // Hardware::display.setTextColour(valueColour(Value::MAX));
            // Hardware::display.print(maxValue);
            dirtyValue = false;
        }
    }
}

Colour RangeParameterField::valueColour(Value value) {
    if(value == selectedValue) {
        return SELECTED_COLOUR;
    } else {
        return VALUE_COLOUR;
    }
}
