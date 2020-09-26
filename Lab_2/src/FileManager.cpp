#include "FileManager.h"
#include "experimental/filesystem"

int FileManager::replaceFile(const char *oldName, const char *newName)
{
    return rename(oldName, newName);
}

int FileManager::removeFile(const char *fileName)
{
    return remove(fileName);
}

int FileManager::copyFile(std::experimental::filesystem::path fileToCopy, std::experimental::filesystem::path destination)
{
    try
    {
        fs::create_directories(destination);
        fs::copy_file(fileToCopy, destination / fileToCopy.filename(), fs::copy_options::overwrite_existing);
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
        return -1;
    }
    return 0;
}