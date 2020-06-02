#include "AppData.h"

#include <Arduino.h>

void AppData::populateTestData() {
    SequencePattern* pattern1 = new SequencePattern(1);
    patterns.add(pattern1);
    SequencePattern* pattern2 = new SequencePattern(2);
    patterns.add(pattern2);

    sequence.channels[0].patterns.add(pattern1);
    sequence.channels[0].patterns.add(NULL);
    sequence.channels[0].patterns.add(pattern1);

    sequence.channels[1].patterns.add(NULL);
    sequence.channels[1].patterns.add(pattern2);
    sequence.channels[1].patterns.add(pattern2);
}
