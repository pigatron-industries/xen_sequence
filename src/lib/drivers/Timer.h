#ifndef Timer_h
#define Timer_h

#include <inttypes.h>


class Timer {

public:
    Timer();
    void start(unsigned long waitTime);
    void stop();
    bool isRunning();
    bool isFinished();

private:
    bool _running = false;
    bool _interrupted = true;
    unsigned long _startTime;
    unsigned long _waitTime;

    void update();

};

#endif
