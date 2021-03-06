#include "FileView.h"
#include "interface/Hardware.h"
#include "interface/components/field/ParameterField.h"
#include "interface/components/DisplayUtils.h"
#include "model/AppData.h"
#include "repository/Config.h"
#include "lib/util/debug.h"

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
    DEBUG("FileView::init");
    listFiles();

    saveConfirmation = false;
    loadConfirmation = false;
    removeConfirmation = false;

    Hardware::keyboard.clear();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::MAGENTA);
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PLAY_STOP, LedColour::GREEN);
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PREV, LedColour::RED);
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_NEXT, LedColour::RED);
}

void FileView::render(GraphicsContext& g) {
    DEBUG("FileView::render")
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

        case InterfaceEventType::KEY_PREV: //REMOVE
            if(event.data == EVENT_KEY_PRESSED) {
                confirmRemove();
            }
            break;

        case InterfaceEventType::KEY_NEXT: //CLEAR
            if(event.data == EVENT_KEY_PRESSED) {
                if(confirmClear()) {
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
    DEBUG("FileView::listFiles")

    selectedIndex = 0;
    DataRepository::data.loadFileList(currentDirectory);
    FileList& fileList = DataRepository::data.getFileList();

    listComponent.clear();
    listComponent.addComponent(&newFileComponent);
    for(int i = 0; i < fileList.size; i++) {
        fileComponents[i].setText(fileList.file[i].filename);
        listComponent.addComponent(&fileComponents[i]);

        DEBUG(fileList.file[i].filepath)
        DEBUG(Config::config.lastFile)

        if(strcmp(fileList.file[i].filepath, Config::config.lastFile) == 0) {
            selectedIndex = i+1;
        }
    }
}

void FileView::save() {
    String path = getSelectedFilePath();
    DataRepository::data.saveSequence(path);
}

void FileView::load() {
    String path = getSelectedFilePath();
    DataRepository::data.loadSequence(path);
}

void FileView::remove() {
    String path = getSelectedFilePath();
    DataRepository::data.removeSequence(path);
    init();
    queueRender(true);
}

void FileView::clear() {
    AppData::data.clear();
    Config::config.lastFile[0] = '\0';
    DataRepository::data.saveConfig();
}

bool FileView::confirmLoad() {
    if(getSelectedType() == SelectedType::EXISTING_FILE) {
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
    SelectedType type = getSelectedType();
    if(type == SelectedType::EXISTING_FILE || type == SelectedType::NEW_FILE) {
        if(saveConfirmation) {
            save();
            return true;
        } else {
            DisplayUtils::drawDialog("Save?", 50, 16);
            saveConfirmation = true;
            return false;
        }
    }
    return false;
}

bool FileView::confirmRemove() {
    if(getSelectedType() == SelectedType::EXISTING_FILE) {
        if(removeConfirmation) {
            remove();
            return true;
        } else {
            DisplayUtils::drawDialog("Delete?", 50, 16);
            removeConfirmation = true;
            return false;
        }
    }
    return false;
}

bool FileView::confirmClear() {
    if(clearConfirmation) {
        clear();
        return true;
    } else {
        DisplayUtils::drawDialog("Clear?", 50, 16);
        clearConfirmation = true;
        return false;
    }
    return false;
}

void FileView::cancelDialog() {
    if(saveConfirmation || loadConfirmation) {
        saveConfirmation = false;
        loadConfirmation = false;
        removeConfirmation = false;
        queueRender(true);
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

String FileView::getSelectedFilePath() {
    return currentDirectory + getSelectedFileName().c_str();
}

String FileView::getSelectedFileName() {
    switch(getSelectedType()) {
        case SelectedType::NEW_FILE:
            return String(Hardware::time.getDateTime()) + F(".seq");
            break;
        case SelectedType::EXISTING_FILE: {
                TextComponent* component = static_cast<TextComponent*>(listComponent.getComponent(selectedIndex));
                return component->getText();
            }
            break;
        case SelectedType::CHILD_DIRECTORY:
            return ""; //TODO
            break;
        case SelectedType::PARENT_DIRECTORY:
            return ""; //TODO
            break;
    }
    return "";
}

SelectedType FileView::getSelectedType() {
    TextComponent* component = static_cast<TextComponent*>(listComponent.getComponent(selectedIndex));
    if(component == &newFileComponent) {
        return SelectedType::NEW_FILE;
    } else {
        return SelectedType::EXISTING_FILE;
    }
}
