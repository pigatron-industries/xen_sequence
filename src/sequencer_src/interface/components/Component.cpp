#include "Component.h"
#include "interface/views/Org_01.h"
#include "lib/util/debug.h"

void Component::render(GraphicsContext& g) {
    top = g.yPos;
}

void Component::render(bool full) { 
    DEBUGINFO
    GraphicsContext g = GraphicsContext(full); 
    if(full) {
        Hardware::display.fillScreen(Colour::BLACK);
    }
    Hardware::display.setFont(Org_01);
    Hardware::display.setTextSize(1);
    render(g); 
}
