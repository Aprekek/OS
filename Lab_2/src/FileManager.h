#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <dirent.h>

namespace fs = std::experimental::filesystem;

class FileManager
{

public:
    static int replaceFile(const char *oldName, const char *newName);
    static int removeFile(const char *fileName);
    static int copyFile(fs::path fileToCopy, fs::path destination);
    static int showContent(const char *dirName);
};

#endif