#include "SongParameterView.h"
#include "model/AppData.h"
#include "sequencer/Sequencer.h"

SongParameterView::SongParameterView() {
    fields.addComponent(&songSpeedField);
    fields.addComponent(&songSpeedMultField);
    setSelectedField(0);
}

void SongParameterView::init() {
    songSpeedField.setValue(AppData::data.getSequence().getSpeed());
    songSpeedMultField.setValue(AppData::data.getSequence().getSpeedMult());
}

void SongParameterView::updateDataFromField(ParameterField* field) {
    if(field == &songSpeedField) {
        AppData::data.getSequence().setSpeed(songSpeedField.getValue());
        Sequencer::sequencer.updateBarSpeed();
    } else if(field == &songSpeedMultField) {
        AppData::data.getSequence().setSpeedMult(songSpeedMultField.getValue());
        Sequencer::sequencer.updateBarSpeed();
    }
}
