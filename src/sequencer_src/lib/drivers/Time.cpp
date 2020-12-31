#include "Time.h"

#include <TimeLib.h>

time_t getTeensyTime() {
  return Teensy3Clock.get();
}

void Time::init() {
    setSyncProvider(getTeensyTime);
}

char* Time::getDateTime() {
    snprintf(datetime, sizeof(datetime), "%04d-%02d-%02d-%02d%02d%02d", year(), month(), day(), hour(), minute(), second());
    Serial.println(datetime);
    return datetime;
}
