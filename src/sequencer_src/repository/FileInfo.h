#ifndef FileInfo_h
#define FileInfo_h

#define MAX_FILENAME_SIZE 32
#define MAX_FILE_COUNT 255

class FileInfo {
    public:
        char filename[MAX_FILENAME_SIZE];
};

class FileList {
    public:
        int size;
        FileInfo file[];
};

#endif