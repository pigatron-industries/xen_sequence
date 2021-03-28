#ifndef RangeParameterField_h
#define RangeParameterField_h

#include "ParameterField.h"

class RangeParameterField : public ParameterField {

public:
    enum Value {
        NONE,
        MIN,
        MAX
    };

    RangeParameterField(const char* name, int16_t min, int16_t max);
    virtual void increment(int16_t amount);
    virtual void decrement(int16_t amount);
    virtual void changeSelectMode();
    virtual void render(GraphicsContext& graphicsContext);

    void setMinValue(int16_t minVvalue);
    void setMaxValue(int16_t maxValue);
    uint16_t getMinValue() { return minValue; }
    uint16_t getMaxValue() { return maxValue; }

private:
    Value selectedValue;
    int16_t minValue;
    int16_t maxValue;
    int16_t min;
    int16_t max;

    Colour valueColour(Value field);

};


#endif
