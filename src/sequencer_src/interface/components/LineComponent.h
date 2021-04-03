#ifndef LineComponent_h
#define LineComponent_h

#include "Component.h"

class LineComponent : public Component {

public:
    LineComponent(Colour lineColour, int height);
    virtual void render(GraphicsContext& g);
    void setLineColour(Colour lineColour) { this->lineColour = lineColour; }

private:

    Colour lineColour;

};


#endif
