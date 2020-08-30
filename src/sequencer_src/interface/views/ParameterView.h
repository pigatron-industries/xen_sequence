#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "../View.h"
#include "SequenceMatrixView.h"
#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"
#include "../components/IntegerParameterField.h"
#include "../components/BooleanParameterField.h"

enum ParameterViewMode {
    PARAM_MODE_BAR, // Track length
    PARAM_MODE_CHANNEL, // Edit entire channel: Mute, length
    PARAM_MODE_EVENT //Edit note parameters
};

enum class ParameterViewSelectionMode {
    SELECT_PARAMETER,
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


class ParameterView : public View {

public:
    ParameterView(AppData& _appData, Sequencer& _sequencer, Display& _display, SequenceMatrixView& _sequenceMatrixView);
    virtual void render(bool full = false);
    virtual void handleEvent(InterfaceEvent event);

    void setBar(uint16_t _barIndex);

private:
    AppData& appData;
    Sequencer& sequencer;
    Display& display;
    SequenceMatrixView& sequenceMatrixView;

    bool dirtyScreen = true;

    uint16_t barIndex = 0;
    SequenceBar* bar;
    SequencePattern* selectedPattern;
    SequenceEvent* selectedEvent;

    ParameterViewMode parameterViewMode = PARAM_MODE_BAR;
    ParameterViewSelectionMode selectionMode = ParameterViewSelectionMode::SELECT_PARAMETER;

    int8_t selectedFieldIndex = 0;
    ParameterField* selectedField = NULL;
    LinkedList<ParameterField*>* visibleFields;

    LinkedList<ParameterField*> barFields;
    IntegerParameterField barLengthField = IntegerParameterField("LENGTH", 1, 255);
    IntegerParameterField barSpeedField = IntegerParameterField("SPEED", 30, 960, " BPM");
    LinkedList<ParameterField*> channelFields;
    BooleanParameterField channelMuteField = BooleanParameterField("MUTE");
    LinkedList<ParameterField*> eventFields;
    IntegerParameterField eventNoteField = IntegerParameterField("NOTE", 0, 128);
    IntegerParameterField eventVelocityField = IntegerParameterField("VELOCITY", 0, 128);
    IntegerParameterField eventGateField = IntegerParameterField("GATE", 0, 100, " %");
    IntegerParameterField eventDelayField = IntegerParameterField("DELAY", 0, 100, " %");

    // rendering
    void renderMode();
    void renderFields();
    void renderField(uint8_t row);
    void setDirtyScreen();

    // events
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

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

    void updateSelectedBar();
    void updateSelectedChannel();
    void updateSelectedEvent();
    void updateDataFromField(ParameterField* field);

    void addEvent();
    void deleteEvent();
};

#endif