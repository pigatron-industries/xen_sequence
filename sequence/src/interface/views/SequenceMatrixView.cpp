#include "SequenceMatrixView.h"


SequenceMatrixView::SequenceMatrixView(AppData& _appData, Matrix& _matrix):
    appData(_appData),
    matrix(_matrix) {
}

void SequenceMatrixView::displayBar(int bar) {
    for(uint8_t channel = 0; channel < SEQUENCE_CHANNELS; channel++) {
        SequencePattern* pattern = appData.getSequence().getChannel(channel).getPatterns().get(bar);
        if(pattern != NULL) {
            for(uint8_t i = 0; i < MATRIX_COLS; i++) {
                if(pattern->getEvents().get(i) != NULL) {
                    matrix.setPixel(channel, i, CRGB::Blue);
                } else {
                    matrix.setPixel(channel, i, CRGB::Black);
                }
            }
        } else {
            for(uint8_t i = 0; i < MATRIX_COLS; i++) {
                matrix.setPixel(channel, i, CRGB::Black);
            }
        }
    }
    matrix.update();
}
