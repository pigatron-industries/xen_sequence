#ifndef StringComponent_h
#define StringComponent_h

#include "Component.h"


class TextComponent : public Component {

public:
    TextComponent();
    virtual void render(GraphicsContext& g);

protected:
    char text[32];

};


#endif
