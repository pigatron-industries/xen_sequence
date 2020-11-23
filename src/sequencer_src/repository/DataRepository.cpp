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

void DataRepository::loadFileList(char* directoryName) {
    File dir = sd.open(directoryName);
    if(dir.isDirectory()) {
        int i = 0;
        fileList.size = 0;
        File entry = dir.openNextFile();
        while(entry) {
            entry.getName(fileList.file[i].filename, MAX_FILENAME_SIZE);
            entry.close();
            //Serial.println(fileList.file[i].filename);
            fileList.size++;
            entry = dir.openNextFile();
        }
    }
}

void DataRepository::listFiles() {
    loadFileList("/sequence");
    for(int i = 0; i < fileList.size; i++) {
        Serial.println(fileList.file[i].filename);
    }
}

void DataRepository::saveData() {
    SdFile file;
    // sd.chdir("/sequence");
    // file.open("text.txt", FILE_WRITE);
    // file.println("test data");
    // file.close();
}

void DataRepository::loadData() {

}