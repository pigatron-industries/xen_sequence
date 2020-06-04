#ifndef SequenceMatrixView_h
#define SequenceMatrixView_h

#include <inttypes.h>

#include "../../model/AppData.h"
#include "../../lib/drivers/Matrix.h"


class SequenceMatrixView {

public:
    SequenceMatrixView(AppData& _appData, Matrix& _matrix);
    void displayBar(int bar);

private:
    AppData& appData;
    Matrix& matrix;
    SequencePattern* patterns[SEQUENCE_CHANNELS];

};

#endif
