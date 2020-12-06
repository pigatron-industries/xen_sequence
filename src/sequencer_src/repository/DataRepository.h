#ifndef DataRepository_h
#define DataRepository_h

#include <SdFat.h>
#include <ArduinoJson.h>
#include "FileInfo.h"

#define JSON_BUF_SIZE 2048
#define JSON_DOC_SIZE 2048

class DataRepository {
    public:
        static DataRepository data;

        void init();

        void loadFileList(String directoryName);
        FileList& getFileList() { return fileList; }
        
        void saveSequence(String path);
        void loadSequence(String path);

    private:
        static const String ROOT_DIRECTORY;

        DataRepository() {}
        SdFat sd;

        FileList fileList;

        size_t serializeSequence(char* buffer, size_t bufferSize);
        void deserializeSequence(char* buffer, size_t bufferSize);
};

#endif