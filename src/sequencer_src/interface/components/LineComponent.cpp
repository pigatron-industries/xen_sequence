#include "LineComponent.h"
#include "lib/util/debug.h"

#define LINE_WIDTH 128 // TODO get max width of display

LineComponent::LineComponent(Colour lineColour, int height) {
    this->height = height;
    this->width = LINE_WIDTH;
    this->lineColour = lineColour;
}

void LineComponent::render(GraphicsContext& g) {
    Hardware::display.fillRect(0, g.yPos, width, height, lineColour);
}
