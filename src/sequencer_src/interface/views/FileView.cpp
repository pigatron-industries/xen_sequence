#include "FileView.h"
#include "../Hardware.h"
#include "../components/ParameterField.h"

FileView::FileView() {
    for(int i = 0; i < MAX_FILES; i++) {
        textComponents[i].setTextColour(Colour::YELLOW);
    }
    titleComponent.setText("SAVE / LOAD");
    titleComponent.setTextColour(Colour::WHITE);
}

void FileView::init() {
    DataRepository::data.loadFileList(currentDirectory);

    listComponent.clear();
    FileList& fileList = DataRepository::data.getFileList();
    listSize = fileList.size;
    for(int i = 0; i < fileList.size; i++) {
        textComponents[i].setText(fileList.file[i].filename);
        listComponent.addComponent(&textComponents[i]);
    }

    selectedComponent = &textComponents[0];

    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::MAGENTA);
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::YELLOW);
}

void FileView::render(GraphicsContext& g) {
    g.focus = selectedComponent;
    if(g.full) {
        titleComponent.render(g);
    }
    g.yPos += titleComponent.getHeight();
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
            View::render(false);
            break;
        case InterfaceEventType::STICK_UP:
            selectedIndex--;
            if(selectedIndex < 0) {
                selectedIndex = listSize-1;
            }
            selectedComponent = &textComponents[selectedIndex];
            View::render(false);
            break;
        case InterfaceEventType::KEY_RECORD: //SAVE
            if(event.data == EVENT_KEY_PRESSED) {
                save();
            }
            break;
        case InterfaceEventType::KEY_PLAY_STOP: //LOAD
            if(event.data == EVENT_KEY_PRESSED) {
                load();
            }
            break;
        default:
            break;
    }
}

void FileView::save() {
    String path = String(currentDirectory).concat(textComponents[selectedIndex].getText());
    DataRepository::data.saveSequence(path);
}

void FileView::load() {
    String path = String(currentDirectory).concat(textComponents[selectedIndex].getText());
    DataRepository::data.loadSequence(path);
}
