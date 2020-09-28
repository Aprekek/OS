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
        if (strcmp(contentInfo->d_name, ".") != 0 && strcmp(contentInfo->d_name, "..") != 0)
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
        closedir(dir);
        return contentSize;
    }
    else
    {
        return fileInfo.st_size;
    }
}

int FileManager::showProcfsProcesses()
{
    DIR *dir = opendir("/proc/");
    if (dir == nullptr)
    {
        return -1;
    }
    dirent *contentInfo;

    std::cout << std::setiosflags(std::ios::left);
    std::cout << std::setw(20) << "COMM";
    std::cout << std::setw(6) << "PID";
    std::cout << std::setw(6) << "STATE";
    std::cout << std::setw(6) << "PPID";
    std::cout << std::setw(6) << "NICE" << std::endl;

    while ((contentInfo = readdir(dir)) != nullptr)
    {
        char *pid = getContent(contentInfo->d_name);
        if (atoi(pid) != 0)
        {
            std::string pidPath = "/proc/";
            pidPath += pid;

            std::ifstream pidInfo(pidPath + "/stat", std::ios_base::in);
            if (!pidInfo.is_open())
            {
                std::string error = "Cannot open file " + pidPath;
                throw error;
            }

            std::cout << std::setw(20) << getPidInfo(pidInfo, 2);
            std::cout << std::setw(6) << pid;
            std::cout << std::setw(6) << getPidInfo(pidInfo, 1);
            std::cout << std::setw(6) << getPidInfo(pidInfo, 1);
            std::cout << std::setw(6) << getPidInfo(pidInfo, 15) << std::endl;
        }
        delete pid;
    }

    closedir(dir);
    return 0;
}

char *FileManager::getContent(char *str)
{
    char *buf = new char(64);
    char ch;
    int i = 0;

    do
    {
        ch = str[i];
        buf[i] = ch;
        ++i;
    } while (ch != '\\' && ch != '\0');

    buf[i] = '\0';

    return buf;
}

std::string FileManager::getPidInfo(std::ifstream &file, const int &offset)
{
    std::string buf;
    for (int i = 0; i < offset; i++)
    {
        buf.clear();
        file >> buf;
    }
    return buf;
}