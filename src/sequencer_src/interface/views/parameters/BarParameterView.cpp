#include "BarParameterView.h"

BarParameterView::BarParameterView() {
    fields.addComponent(&barLengthField);
    fields.addComponent(&barSpeedField);
    fields.addComponent(&barSpeedMultField);
}

void BarParameterView::setBar(SequenceBar* bar) {
    this->bar = bar;
    barLengthField.setValue(bar->getLength());
    barSpeedField.setValue(bar->getSpeedDiff());
    barSpeedMultField.setValue(bar->getSpeedMult());
}