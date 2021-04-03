#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "View.h"
#include "matrix/SequenceMatrixView.h"
#include "parameters/BarParameterView.h"
#include "parameters/ChannelParameterView.h"
#include "parameters/TickEventsParameterView.h"
#include "parameters/SongParameterView.h"
#include "sequencer/midi/MidiEventHandler.h"

enum ParameterViewMode {
    PARAM_MODE_SONG,
    PARAM_MODE_BAR, // Track length
    PARAM_MODE_CHANNEL, // Edit entire channel: Mute, length
    PARAM_MODE_EVENT //Edit note parameters
};

enum class ParameterViewSelectionMode {
    SELECT_NONE,
    SELECT_CHANNEL,
    SELECT_EVENT
};


class ParameterView : public View, public MidiEventHandler {

public:
    ParameterView(SequenceMatrixView& _sequenceMatrixView);
    virtual void init();
    virtual void render(GraphicsContext& g);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);
    virtual void handleMidiEvent(MidiMessage message);

    void setBar(uint16_t _barIndex);

private:
    SequenceMatrixView& sequenceMatrixView;

    bool recording;

    bool dirtyScreen = true;

    uint16_t barIndex = 0;
    SequencePattern* selectedPattern;

    SequenceTickEvents* copiedEvent;
    bool dragging;
    int draggingFromBar;
    int draggingFromChannel;
    int draggingFromTick;

    ParameterViewMode parameterViewMode = PARAM_MODE_EVENT;
    ParameterViewSelectionMode selectionMode = ParameterViewSelectionMode::SELECT_EVENT;

    AbstractParameterView* visibleParameterView;

    SongParameterView songParameterView;
    BarParameterView barParameterView;
    ChannelParameterView channelParameterView;
    TickEventsParameterView tickEventsParameterView;

    // rendering
    void renderMode();
    void setDirtyScreen();

    void renderKeyLeds();

    // events
    void record(bool value);

    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

    void nextBar();
    void prevBar();

    void fieldIncrement(int amount);
    void fieldDecrement(int amount);

    void cycleSelectionMode();
    void setSelectionMode(ParameterViewSelectionMode _selectionMode);
    void cycleParameterViewMode();
    void setParameterViewMode(ParameterViewMode _parameterViewMode);
    ParameterField* getSelectedField();
    void nextParameter();
    void prevParameter();

    void updateSelectedBarFields();
    void updateSelectedChannelFields();
    void updateSelectedEventFields();

    void addEvent();
    void addEvent(SequenceTickEvents* copy);
    void deleteEvent();
    void clearPattern();

    void copy();
    void paste();
    void drag();
    void drop();
};

#endif
