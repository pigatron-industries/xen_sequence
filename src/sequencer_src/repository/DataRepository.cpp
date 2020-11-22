#include "DataRepository.h"

DataRepository DataRepository::data;

void DataRepository::init() {
    if (!sd.begin(SdioConfig(FIFO_SDIO))) {
        Serial.println("SD card init failed");
        return;
    }

    if(!sd.exists("/sequence")) {
        Serial.println("Creating sequence directory");
        sd.mkdir("/sequence", true);
    }

    listFiles();
}

void DataRepository::listFiles() {
    File dir = sd.open("/sequence");
    if(dir.isDirectory()) {
        File entry = dir.openNextFile();
        while(entry) {
            char filename[MAX_FILENAME_SIZE];
            entry.getName(filename, MAX_FILENAME_SIZE);
            entry.close();
            Serial.println(filename);
            entry = dir.openNextFile();
        }
    }
}

void DataRepository::saveData() {
    // SdFile file;
    // sd.chdir("/sequence");
    // file.open("text.txt", FILE_WRITE);
    // file.println("test data");
    // file.close();
}

void DataRepository::loadData() {

}