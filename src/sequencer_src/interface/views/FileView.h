#ifndef FileView_h
#define FileView_h

#include <inttypes.h>

#include "../View.h"
#include "../../repository/DataRepository.h"


class FileView : public View {

public:
    FileView();
    void load();
    virtual void render(bool full = false);
    virtual void handleEvent(InterfaceEvent event);

private:
    char currentDirectory[MAX_FILENAME_SIZE];

};

#endif
