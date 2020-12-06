#ifndef StringComponent_h
#define StringComponent_h

#include "Component.h"
#include "../Hardware.h"

class TextComponent : public Component {

public:
    TextComponent();
    virtual void render(GraphicsContext& g);
    void setText(const char* text);
    void setTextColour(Colour textColour) { this->textColour = textColour; }
    char* getText() { return text; }

private:
    char text[32];

    Colour textColour;

};


#endif
