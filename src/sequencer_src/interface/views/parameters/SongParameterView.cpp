#include "SongParameterView.h"
#include "model/AppData.h"

SongParameterView::SongParameterView() {
    fields.addComponent(&songSpeedField);
    fields.addComponent(&songSpeedMultField);
}

void SongParameterView::init() {
    songSpeedField.setValue(AppData::data.getSequence().getSpeed());
    songSpeedMultField.setValue(AppData::data.getSequence().getSpeedMult());
}
