#ifndef RangeParameterField_h
#define RangeParameterField_h

#include "ParameterField.h"
#include "lib/util/RangeScale.h"

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

    void setStartValue(int16_t startValue);
    void setStopValue(int16_t stopValue);
    uint16_t getStartValue() { return startValue; }
    uint16_t getStopValue() { return stopValue; }

private:
    Value selectedValue;
    int16_t startValue;
    int16_t stopValue;
    int16_t min;
    int16_t max;

    RangeScale scale;

    Colour valueColour(Value field);

};


#endif
