#include "FileView.h"
#include "../Hardware.h"
#include "../components/ParameterField.h"
#include "../components/DisplayUtils.h"

FileView::FileView() {
    for(int i = 0; i < MAX_FILES; i++) {
        fileComponents[i].setTextColour(Colour::YELLOW);
    }
    titleComponent.setText("SAVE / LOAD");
    titleComponent.setTextColour(Colour::WHITE);
    newFileComponent.setText(" [ NEW FILE ] ");
    newFileComponent.setTextColour(Colour::YELLOW);
}

void FileView::init() {
    listFiles();

    saveConfirmation = false;
    loadConfirmation = false;

    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::MAGENTA);
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::YELLOW);
}

void FileView::render(GraphicsContext& g) {
    g.focus = listComponent.getComponent(selectedIndex);
    if(g.full) {
        titleComponent.render(g);
    }
    g.yPos += titleComponent.getHeight();
    listComponent.render(g);

    Hardware::display.updateScreen();
}

InterfaceEvent FileView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::STICK_DOWN:
            cancelDialog();
            selectedIndex++;
            if(selectedIndex >= listComponent.getSize()) {
                selectedIndex = 0;
            }
            queueRender();
            break;

        case InterfaceEventType::STICK_UP:
            cancelDialog();
            selectedIndex--;
            if(selectedIndex < 0) {
                selectedIndex = listComponent.getSize()-1;
            }
            queueRender();
            break;

        case InterfaceEventType::STICK_PRESS:
            navigate();
            break;

        case InterfaceEventType::KEY_RECORD: //SAVE
            if(event.data == EVENT_KEY_PRESSED) {
                if(confirmSave()) {
                    return InterfaceEvent(InterfaceEventType::KEY_VIEW);
                }
            }
            break;

        case InterfaceEventType::KEY_PLAY_STOP: //LOAD
            if(event.data == EVENT_KEY_PRESSED) {
                if(confirmLoad()) {
                    return InterfaceEvent(InterfaceEventType::KEY_VIEW);
                }
            }
            break;

        default:
            break;
    }

    return InterfaceEvent::NONE;
}

void FileView::listFiles() {
    DataRepository::data.loadFileList(currentDirectory);
    FileList& fileList = DataRepository::data.getFileList();

    listComponent.clear();
    listComponent.addComponent(&newFileComponent);
    for(int i = 0; i < fileList.size; i++) {
        fileComponents[i].setText(fileList.file[i].filename);
        listComponent.addComponent(&fileComponents[i]);
    }

    selectedIndex = 0;
}

void FileView::save() {
    //TODO check selected component is file
    TextComponent* component = static_cast<TextComponent*>(listComponent.getComponent(selectedIndex));
    if(component != &newFileComponent) {
        String path = String(currentDirectory).concat(component->getText());
        DataRepository::data.saveSequence(path);
    }
}

void FileView::load() {
    //TODO check selected component is file
    TextComponent* component = static_cast<TextComponent*>(listComponent.getComponent(selectedIndex));
    if(component != &newFileComponent) {
        String path = String(currentDirectory).concat(component->getText());
        DataRepository::data.loadSequence(path);
    }
}

bool FileView::confirmLoad() {
    TextComponent* component = static_cast<TextComponent*>(listComponent.getComponent(selectedIndex));
    if(component != &newFileComponent) {
        if(loadConfirmation) {
            load();
            return true;
        } else {
            DisplayUtils::drawDialog("Load?", 50, 16);
            loadConfirmation = true;
            return false;
        }
    }
    return false;
}

bool FileView::confirmSave() {
    if(saveConfirmation) {
        save();
        return true;
    } else {
        DisplayUtils::drawDialog("Save?", 50, 16);
        saveConfirmation = true;
        return false;
    }
}

void FileView::cancelDialog() {
    if(saveConfirmation || loadConfirmation) {
        saveConfirmation = false;
        loadConfirmation = false;
        queueRender();
    }
}

void FileView::navigate() {
    String path = String(currentDirectory).concat(fileComponents[selectedIndex].getText());
    if(DataRepository::data.loadFileList(path)) {
        currentDirectory = path;
        //TODO
        queueRender();
    }
}