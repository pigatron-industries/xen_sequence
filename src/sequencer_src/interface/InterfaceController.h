#ifndef InterfaceController_h
#define InterfaceController_h

#include <inttypes.h>

#include "sequencer/Sequencer.h"
#include "sequencer/SequencerEventListener.h"

#include "InterfaceEvent.h"
#include "Keyboard.h"
#include "views/View.h"
#include "views/SequenceView.h"
#include "views/ParameterView.h"
#include "views/FileView.h"
#include "views/HelpView.h"
#include "views/matrix/SequenceMatrixView.h"

class InterfaceController : public SequencerEventListener {

public:
    InterfaceController();
    void init();
    void render();
    void handleEvent(InterfaceEvent event);
    virtual void onTick();

private:
    View* currentView;
    View* previousView;

    SequenceMatrixView sequenceMatrixView;
    SequenceView sequenceView;
    ParameterView parameterView;
    FileView fileView;
    HelpView helpView;

    void switchToParameterView();
    void switchToSequenceView();

    bool isSequenceView() { return currentView == &sequenceView || currentView == &parameterView; }
    bool isHelpView() { return currentView == &helpView; }
    bool isFileView() { return currentView == &fileView; }

    void play();
    void stop();
    // void record(bool value);

    void cycleLoopMode();
    void setLoopMode(SequencePlayMode loopMode);

};

#endif
