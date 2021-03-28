#include "BarParameterView.h"
#include "sequencer/Sequencer.h"

BarParameterView::BarParameterView() {
    fields.addComponent(&barLengthField);
    fields.addComponent(&barSpeedField);
    fields.addComponent(&barSpeedMultField);
    setSelectedField(0);
}

void BarParameterView::setBar(SequenceBar* bar) {
    this->bar = bar;
    barLengthField.setValue(bar->getLength());
    barSpeedField.setValue(bar->getSpeedDiff());
    barSpeedMultField.setValue(bar->getSpeedMult());
}

void BarParameterView::updateDataFromField(ParameterField* field) {
    if(field == &barSpeedField) {
        bar->setSpeedDiff(barSpeedField.getValue());
        if(Sequencer::sequencer.getCurrentBar() == bar) {
            Sequencer::sequencer.updateBarSpeed();
        }
    } else if(field == &barSpeedMultField) {
        bar->setSpeedMult(barSpeedMultField.getValue());
        if(Sequencer::sequencer.getCurrentBar() == bar) {
            Sequencer::sequencer.updateBarSpeed();
        }
    }
}