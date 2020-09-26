#include "FileManager.h"

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

int FileManager::showContent(const char *dirName)
{
    DIR *dir = opendir(dirName);
    if (dir == nullptr)
    {
        std::cout << "Неудалось открыть каталог" << dirName << std::endl;
        return -1;
    }

    dirent *contentInfo;
    std::cout << "Содержимое каталога " << dirName << ":\n";
    while ((contentInfo = readdir(dir)) != nullptr)
    {
        std::cout << contentInfo->d_name << std::endl;
    }
    closedir(dir);
    return 0;
}

unsigned long FileManager::size(std::string fileName)
{
    unsigned long contentSize = 0;

    struct stat fileInfo;
    if (stat(fileName.c_str(), &fileInfo) != 0)
    {
        std::string error = "Cannot get info about file \"" + fileName + "\"";
        throw error;
    }
    if (S_ISDIR(fileInfo.st_mode))
    {
        DIR *dir = opendir(fileName.c_str());
        if (dir == nullptr)
        {
            std::string error = "Cannot open dir \"" + fileName + "\"";
            throw error;
        }

        dirent *contentInfo;
        while ((contentInfo = readdir(dir)) != nullptr)
        {
            if ((strcmp(contentInfo->d_name, ".") != 0) && (strcmp(contentInfo->d_name, "..") != 0))
            {
                std::string pathToNestedFile = fileName + "/" + contentInfo->d_name;
                contentSize += size(pathToNestedFile);
            }
        }
        return contentSize;
    }
    else
    {
        return fileInfo.st_size;
    }
}