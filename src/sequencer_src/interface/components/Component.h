#ifndef Component_h
#define Component_h

#include <inttypes.h>
#include "interface/graphics/GraphicsContext.h"
#include "interface/Hardware.h"

class Component : public Focusable {

public:
    Component() {}
    virtual void render(GraphicsContext& graphicsContext) = 0;
    void render(bool full = true);

    uint8_t getHeight() { return height; }
    uint8_t getWidth() { return width; }
    bool getVisibility() { return visible; }
    bool getFocusable() { return focusable; }

    void setVisibility(bool visible) { this->visible = visible; }
    void setFocusable(bool focusable) { this->focusable = focusable; }

protected:
    uint8_t height;
    uint8_t width;
    bool visible = true;
    bool focusable = false;

};


#endif
