#include "RangeParameterField.h"

RangeParameterField::RangeParameterField(const char* name, int16_t min, int16_t max) :
    ParameterField(name), 
    scale(min, max, FIELD_NAME_WIDTH, FIELD_WIDTH-3) {
        this->min = min;
        this->max = max;
        selectedValue = Value::NONE;
}

void RangeParameterField::setStartValue(int16_t startValue) { 
    this->startValue = startValue; 
    dirtyValue = true; 
}

void RangeParameterField::setStopValue(int16_t stopValue) { 
    this->stopValue = stopValue; 
    if(this->stopValue <= startValue) {
        this->stopValue = startValue + 1;
    }
    dirtyValue = true;
}

void RangeParameterField::increment(int16_t amount) {
    if(selectedValue == Value::MIN) {
        startValue += amount;
        if(startValue >= stopValue) {
            startValue = stopValue - 1;
        }
    } else {
        stopValue += amount;
        if(stopValue > max) {
            stopValue = max;
        }
    }
    dirtyValue = true;
}

void RangeParameterField::decrement(int16_t amount) {
    if(selectedValue == Value::MIN) {
        startValue -= amount;
        if(startValue < min) {
            startValue = min;
        }
    } else {
        stopValue -= amount;
        if(stopValue <= startValue) {
            stopValue = startValue + 1;
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

            int startPos = scale.convert(startValue);
            int stopPos = scale.convert(stopValue);
            Hardware::display.fillRect(startPos, g.yPos+2, stopPos-startPos, height-4, Colour::YELLOW);
            Hardware::display.drawLine(startPos, g.yPos+2, startPos, g.yPos+height-3, valueColour(Value::MIN));
            Hardware::display.drawLine(stopPos, g.yPos+2, stopPos, g.yPos+height-3, valueColour(Value::MAX));

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
