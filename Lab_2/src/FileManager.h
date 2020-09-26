#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>

class FileManager
{

public:
    static int replaceFile(const char *oldName, const char *newName);
    static int removeFile(const char *fileName);
};

#endif