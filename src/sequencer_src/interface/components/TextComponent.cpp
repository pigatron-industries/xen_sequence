#include "TextComponent.h"
#include "../Hardware.h"

#define FIELD_HEIGHT 11
#define TEXT_HEIGHT 7

TextComponent::TextComponent() {
    height = FIELD_HEIGHT;
}

void TextComponent::render(GraphicsContext& g) {
    Hardware::display.setTextColour(Colour(0, 128, 255));
    Hardware::display.setCursor(0, g.yPos+TEXT_HEIGHT);
    Hardware::display.print(text);
}
