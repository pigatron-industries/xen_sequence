#ifndef BooleanParameterField_h
#define BooleanParameterField_h

#include "ParameterField.h"

class BooleanParameterField : public ParameterField {

public:
    BooleanParameterField(const char* _name);
    void increment(int16_t amount);
    void decrement(int16_t amount);
    virtual void render(GraphicsContext& graphicsContext);

    void setValue(bool _value) { value = _value; }
    bool getValue() { return value; }

private:
    bool value;

};


#endif
