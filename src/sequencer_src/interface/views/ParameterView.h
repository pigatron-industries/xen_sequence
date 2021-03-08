#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "View.h"
#include "SequenceMatrixView.h"
#include "interface/components/field/PitchParameterField.h"
#include "interface/components/field/IntegerParameterField.h"
#include "interface/components/field/BooleanParameterField.h"
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

enum Parameter {
    PARAM_SELECT,
    PARAM_BAR_LENGTH,
    PARAM_BAR_BPM,
    PARAM_CHANNEL_MUTE,
    PARAM_EVENT_PITCH,
    PARAM_EVENT_GATE,
    PARAM_EVENT_DELAY,
    PARAM_EVENT_RATCHET,
};


class ParameterView : public View, public MidiEventHandler {

public:
    ParameterView(Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView);
    virtual void init();
    virtual void render(GraphicsContext& g);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);
    virtual void handleMidiEvent(MidiMessage message);

    void setBar(uint16_t _barIndex);

private:
    Sequencer& sequencer;
    SequenceMatrixView& sequenceMatrixView;

    bool recording;

    bool dirtyScreen = true;

    uint16_t barIndex = 0;
    SequenceBar* bar;
    SequencePattern* selectedPattern;
    SequenceEvent* selectedEvent;

    SequenceEvent* copiedEvent;
    bool dragging;
    int draggingFromBar;
    int draggingFromChannel;
    int draggingFromTick;

    ParameterViewMode parameterViewMode = PARAM_MODE_EVENT;
    ParameterViewSelectionMode selectionMode = ParameterViewSelectionMode::SELECT_EVENT;

    int8_t selectedFieldIndex = 0;
    ParameterField* selectedField = NULL;
    LinkedList<ParameterField*>* visibleFields;

    LinkedList<ParameterField*> songFields;
    IntegerParameterField songSpeedField = IntegerParameterField("SPEED", 30, 960, " BPM");
    IntegerParameterField songSpeedMultField = IntegerParameterField("SPEEDX", 0, 4, "");

    LinkedList<ParameterField*> barFields;
    IntegerParameterField barLengthField = IntegerParameterField("LENGTH", 1, 255);
    IntegerParameterField barSpeedField = IntegerParameterField("SPEED+", 0, 960, " BPM");
    IntegerParameterField barSpeedMultField = IntegerParameterField("SPEEDX", 0, 4, "");

    LinkedList<ParameterField*> channelFields;
    BooleanParameterField channelMuteField = BooleanParameterField("MUTE");

    LinkedList<ParameterField*> eventFields;
    PitchParameterField eventPitchField = PitchParameterField("PITCH");
    IntegerParameterField eventVelocityField = IntegerParameterField("VELOCITY", 0, 128);
    IntegerParameterField eventGateField = IntegerParameterField("GATE", 0, 100, " %");
    IntegerParameterField eventDelayField = IntegerParameterField("DELAY", 0, 100, " %");

    // rendering
    void renderMode();
    void renderFields();
    void renderField(uint8_t row);
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
    void setSelectedField(int8_t fieldIndex);
    void nextParameter();
    void prevParameter();

    void updateSongFields();
    void updateSelectedBarFields();
    void updateSelectedChannelFields();
    void updateSelectedEventFields();
    void updateDataFromField(ParameterField* field);

    void addEvent();
    void addEvent(SequenceEvent* copy);
    void deleteEvent();
    void clearPattern();

    void copy();
    void paste();
    void drag();
    void drop();
};

#endif
