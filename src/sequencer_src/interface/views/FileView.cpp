#include "FileView.h"
#include "../Hardware.h"
#include "../components/ParameterField.h"

#include "Org_01.h"

FileView::FileView() {
}

void FileView::load() {
    DataRepository::data.loadFileList(currentDirectory);
}

void FileView::render(bool full) {
    Hardware::display.fillScreen(Colour(0, 0, 0));
    Hardware::display.setFont(Org_01);
    Hardware::display.setTextSize(1);
    Hardware::display.setTextColour(Colour::YELLOW);

    Hardware::display.setCursor(0, FIELD_HEIGHT);
    Hardware::display.print(currentDirectory);

    FileList& fileList = DataRepository::data.getFileList();
    for(int i = 0; i < fileList.size; i++) {
        uint8_t top = (i+2)*FIELD_HEIGHT;
        Hardware::display.setCursor(0, top);
        Hardware::display.print(fileList.file[i].filename);
    }

    Hardware::display.updateScreen();
}

void FileView::handleEvent(InterfaceEvent event) {
}
