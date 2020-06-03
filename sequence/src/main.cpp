#include <Arduino.h>

#include "hwconfig.h"

#include "lib/task/TaskManager.h"
#include "lib/drivers/Display.h"
#include "lib/drivers/Matrix.h"
#include "model/AppData.h"
#include "interface/InputTask.h"
#include "interface/InterfaceController.h"



// hardware
Display display = Display();
Matrix matrix = Matrix();

// data
AppData appData = AppData();

// user interface
InterfaceController interfaceController = InterfaceController(appData, display, matrix);
InputTask inputTask = InputTask(interfaceController, STICK_X_PIN, STICK_Y_PIN);



void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*      Pigatron Industries Sequence     *");
    Serial.println("=========================================");
    Serial.println();

    appData.populateTestData();
    matrix.init();
    inputTask.init();
    interfaceController.init();

    while(true) {
        inputTask.execute();
    }
}
