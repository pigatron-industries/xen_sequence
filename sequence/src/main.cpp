#include <Arduino.h>

#include "hwconfig.h"

#include "lib/task/TaskManager.h"
#include "tasks/InputTask.h"


// hardware


InputTask inputTask = InputTask();


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*      Pigatron Industries Sequence     *");
    Serial.println("=========================================");
    Serial.println();

    Task* tasks[] = {&inputTask};
    TaskManager taskManager(tasks, 1);
    taskManager.run();
}
