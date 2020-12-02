#include "FileView.h"
#include "../Hardware.h"
#include "../components/ParameterField.h"

#include "Org_01.h"

FileView::FileView() {
    for(int i = 0; i < MAX_FILES; i++) {
        textComponents[i].setTextColour(Colour::YELLOW);
    }
}

void FileView::load() {
    DataRepository::data.loadFileList(currentDirectory);

    listComponent.clear();
    FileList& fileList = DataRepository::data.getFileList();
    listSize = fileList.size;
    for(int i = 0; i < fileList.size; i++) {
        textComponents[i].setText(fileList.file[i].filename);
        listComponent.addComponent(&textComponents[i]);
    }

    selectedComponent = &textComponents[0];
}

void FileView::render(GraphicsContext& g) {
    g.focus = selectedComponent;

    Hardware::display.fillScreen(Colour(0, 0, 0));
    Hardware::display.setFont(Org_01);
    Hardware::display.setTextSize(1);

    listComponent.render(g);

    Hardware::display.updateScreen();
}

void FileView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::STICK_DOWN:
            selectedIndex++;
            if(selectedIndex >= listSize) {
                selectedIndex = 0;
            }
            selectedComponent = &textComponents[selectedIndex];
            Component::render();
            break;
        case InterfaceEventType::STICK_UP:
            selectedIndex--;
            if(selectedIndex < 0) {
                selectedIndex = listSize-1;
            }
            selectedComponent = &textComponents[selectedIndex];
            Component::render();
            break;
        default:
            break;
    }
}
