#include "TextComponent.h"

#define FIELD_HEIGHT 11
#define FIELD_WIDTH 128 // TODO get max width of display
#define TEXT_HEIGHT 7

TextComponent::TextComponent() {
    height = FIELD_HEIGHT;
    width = FIELD_WIDTH;
}

void TextComponent::render(GraphicsContext& g) {
    if(g.focus == this) {
        Hardware::display.setTextColour(Colour::BLACK);
        Hardware::display.fillRect(0, g.yPos, width, height, textColour);
    } else {
        Hardware::display.setTextColour(textColour);
        Hardware::display.fillRect(0, g.yPos, width, height, Colour::BLACK);
    }
    Hardware::display.setCursor(1, g.yPos+TEXT_HEIGHT);
    Hardware::display.print(text);
}

void TextComponent::setText(const char* text) {
    strcpy(this->text, text);
}