#include "DataRepository.h"
#include "model/AppData.h"
#include "lib/util/debug.h"
#include "./Config.h"

DataRepository DataRepository::data;

const String DataRepository::ROOT_DIRECTORY = String("/sequence");

void DataRepository::init() {
    DEBUGINFO

    if (!sd.begin(SdioConfig(FIFO_SDIO))) {
        ERROR("SD card init failed");
        return;
    }

    if(!sd.exists(ROOT_DIRECTORY)) {
        DEBUGLN("Creating sequence directory");
        sd.mkdir(ROOT_DIRECTORY, true);
    }

    loadConfig();
    if(strlen(Config::config.lastFile) > 0) {
        loadSequence(Config::config.lastFile);
    }
}

bool DataRepository::loadFileList(String directoryName) {
    DEBUGINFO
    File dir = sd.open(String(ROOT_DIRECTORY).concat(directoryName));
    if(dir.isDirectory()) {
        int i = 0;
        fileList.size = 0;
        File entry = dir.openNextFile();
        while(entry) {
            entry.getName(fileList.file[i].filename, MAX_FILENAME_SIZE);
            entry.close();
            String filepath = String().concat(directoryName).concat(fileList.file[i].filename);
            strcpy(fileList.file[i].filepath, filepath.c_str());
            fileList.size++;
            i++;
            entry = dir.openNextFile();
        }
        dir.close();
        return true;
    } else {
        dir.close();
        return false;
    }
}

void DataRepository::saveSequence(String path) {
    DEBUGINFO
    String fullpath = String(ROOT_DIRECTORY).concat(path);
    INFO("Saving to");
    INFO(fullpath);

    char jsonBuffer[JSON_BUF_SIZE];
    size_t jsonSize = serializeSequence(jsonBuffer, JSON_BUF_SIZE);
    DEBUGLN(jsonBuffer);
    INFO("Writing bytes"); 
    INFO(jsonSize);

    SdFile file;
    if(!file.open(fullpath.c_str(), O_WRONLY | O_CREAT | O_TRUNC)) {
        ERROR("Open file failed!");
    }
    file.println(jsonBuffer);
    file.sync();
    file.close();
    INFO("done.");

    strcpy(Config::config.lastFile, path.c_str());
    saveConfig();
}

void DataRepository::loadSequence(String path) {
    String fullpath = String(ROOT_DIRECTORY).concat(path);
    INFO("Loading from"); 
    INFO(fullpath);

    SdFile file;
    if(!file.open(fullpath.c_str(), FILE_READ)) {
        ERROR("Open file failed!");
    }

    char jsonBuffer[JSON_BUF_SIZE];
    int size = file.read(jsonBuffer, JSON_BUF_SIZE);
    Serial.write(jsonBuffer, size);

    deserializeSequence(jsonBuffer, size);

    file.close();
    INFO("done.");

    strcpy(Config::config.lastFile, path.c_str());
    saveConfig();
}

void DataRepository::removeSequence(String path) {
    String fullpath = String(ROOT_DIRECTORY).concat(path);
    INFO("Deleting file"); 
    INFO(fullpath);

    SdFile file;
    if(!file.open(fullpath.c_str(), O_RDWR)) {
        ERROR("Open file failed!");
    }

    if(!file.remove()) {
        ERROR("Delete file failed!");
    }
}

size_t DataRepository::serializeSequence(char* buffer, size_t bufferSize) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    JsonObject docSequence = doc.to<JsonObject>();
    AppData::data.serialize(docSequence);
    return serializeJson(doc, buffer, bufferSize);
}

void DataRepository::deserializeSequence(char* buffer, size_t size) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    deserializeJson(doc, buffer, size);
    JsonObject docSequence = doc.as<JsonObject>();
    AppData::data.deserialize(docSequence);
}

void DataRepository::loadConfig() {
    DEBUGINFO

    SdFile file;
    if(!file.open(CONFIG_FILE, FILE_READ)) {
        ERROR("Open file failed!");
    }

    char jsonBuffer[JSON_BUF_SIZE];
    int size = file.read(jsonBuffer, JSON_BUF_SIZE);

    deserializeConfig(jsonBuffer, size);

    file.close();
}

void DataRepository::saveConfig() {
    DEBUGINFO

    char jsonBuffer[JSON_BUF_SIZE];
    size_t jsonSize = serializeConfig(jsonBuffer, JSON_BUF_SIZE);
    DEBUGLN(jsonBuffer);
    INFO("Writing bytes"); 
    INFO(jsonSize);

    SdFile file;
    if(!file.open(CONFIG_FILE, O_WRONLY | O_CREAT | O_TRUNC)) {
        ERROR("Open file failed!");
    }
    file.println(jsonBuffer);
    file.sync();
    file.close();
}

size_t DataRepository::serializeConfig(char* buffer, size_t bufferSize) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    JsonObject docConfig = doc.to<JsonObject>();
    Config::config.serialize(docConfig);
    return serializeJson(doc, buffer, bufferSize);
}

void DataRepository::deserializeConfig(char* buffer, size_t size) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    deserializeJson(doc, buffer, size);
    JsonObject docConfig = doc.as<JsonObject>();
    Config::config.deserialize(docConfig);
}