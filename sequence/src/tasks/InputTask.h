#ifndef InputTask_h
#define InputTask_h

#include <inttypes.h>

#include "../lib/task/Task.h"


class InputTask : public Task {

public:
    InputTask();
    void init();
    void execute();

private:

};

#endif
