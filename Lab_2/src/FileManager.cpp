#include <string>
#include "FileManager.h"

int FileManager::replaceFile(const char *oldName, const char *newName)
{
    return rename(oldName, newName);
}

int FileManager::removeFile(const char *fileName)
{
    return remove(fileName);
}