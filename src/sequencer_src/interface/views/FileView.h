#ifndef FileView_h
#define FileView_h

#include <inttypes.h>

#include "View.h"
#include "interface/components/ListComponent.h"
#include "interface/components/TextComponent.h"
#include "repository/DataRepository.h"

enum SelectedType {
    EXISTING_FILE,
    NEW_FILE,
    CHILD_DIRECTORY,
    PARENT_DIRECTORY
};

class FileView : public View {

public:
    static const int MAX_FILES = 255;

    FileView();
    virtual void init();
    virtual void render(GraphicsContext& g);
    virtual void handleEvent(InterfaceEvent event);

private:
    String currentDirectory = String("/");
    //char lastFileName[32];
    int selectedIndex;

    TextComponent titleComponent;
    ListComponent listComponent;
    TextComponent newFileComponent;
    TextComponent fileComponents[MAX_FILES];

    bool saveConfirmation;
    bool loadConfirmation;
    bool removeConfirmation;
    bool clearConfirmation;

    void listFiles();

    void save();
    void load();
    void remove();
    void clear();

    bool confirmLoad();
    bool confirmSave();
    bool confirmRemove();
    bool confirmClear();
    void cancelDialog();

    void navigate();

    String getSelectedFilePath();
    String getSelectedFileName();
    SelectedType getSelectedType();

};

#endif
