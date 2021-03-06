#ifndef ParameterField_h
#define ParameterField_h

#include "ParameterFieldListener.h"
#include "lib/drivers/Display.h"
#include "../Component.h"

#define FIELD_HEIGHT 11
#define TEXT_HEIGHT 7
#define FIELD_NAME_WIDTH 48
#define FIELD_VALUE_WIDTH 80
#define FIELD_WIDTH 128 // TODO get max width of display

#define VALUE_COLOUR Colour::YELLOW
#define SELECTED_COLOUR Colour::ORANGE

class ParameterField : public Component {

public:
    enum SelectMode {
        FIELD,
        VALUE
    };
    static SelectMode selectMode;

    ParameterField(const char* _name);
    virtual void increment(int16_t amount) = 0;
    virtual void decrement(int16_t amount) = 0;
    virtual void changeSelectMode();
    virtual void render(GraphicsContext& graphicsContext);

    void setListener(ParameterFieldListener* listener) { this->listener = listener; }
    void setSelected(bool _selected) { selected = _selected; dirtyValue = true; }
    void setDirty() { dirtyLabel = true; dirtyValue = true; }

protected:
    const char* name;
    bool selected = false;

    bool dirtyLabel = true;
    bool dirtyValue = true;

    ParameterFieldListener* listener = NULL;

};


#endif
