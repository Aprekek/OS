#include <iostream>
#include "FileManager.h"
#include <string.h>

const char *MOVE_FILE = "-mv";
const char *DELETE_FLAG = "-dl";
const char *COPY_FLAG = "-cp";
const char *LS_FLAG = "-ls";

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Ошибка! Слишком мало аргументов -h для помощи\n";
        return -1;
    }

    char *flag = nullptr;
    for (int i = 1; i < argc; i++)
    {
        flag = argv[i];
        if (strcmp(flag, MOVE_FILE) == 0)
        {
            if (argc < i + 2) // 2 означает, что присутствуют стрый путь и новый
                std::cout << "Ошибка! Недостаточно аргументов для флага " << MOVE_FILE << std::endl;
            else
            {
                if (FileManager::replaceFile(argv[i + 1], argv[i + 2]) == 0)
                {
                    std::cout << "Файл успешно перенесен!\n";
                }
                else
                {
                    std::cout << "Ошибка! Неудалось переместить файл\n";
                };
                i += 2;
            }
            continue;
        }
        if (strcmp(flag, DELETE_FLAG) == 0)
        {
            if (argc < i + 1)
                std::cout << "Ошибка! Недостаточно аргументов для флага " << DELETE_FLAG << std::endl;
            else
            {
                if (FileManager::removeFile(argv[i + 1]) == 0)
                {
                    std::cout << "Файл успешно удален!\n";
                }
                else
                {
                    std::cout << "Ошибка! Неудалось удалить файл\n";
                };
                ++i;
            }
            continue;
        }
        if (strcmp(flag, COPY_FLAG) == 0)
        {
            if (argc < i + 2)
                std::cout << "Ошибка! Недостаточно аргументов для флага " << COPY_FLAG << std::endl;
            else
            {
                if (FileManager::copyFile(argv[i + 1], argv[i + 2]) == 0)
                {
                    std::cout << "Файл успешно копирован!\n";
                }
                else
                {
                    std::cout << "Ошибка! Неудалось скопировать файл\n";
                };
                i += 2;
            }
            continue;
        }
        if (strcmp(flag, LS_FLAG) == 0)
        {
            if (argc < i + 1)
                std::cout << "Ошибка! Недостаточно аргументов для флага " << LS_FLAG << std::endl;
            else
            {
                FileManager::showContent(argv[i + 1]);
                ++i;
            }
            continue;
        }
        std::cout << "Ошибка! Неизвестный флаг " << flag << std::endl;
    }
    return 0;
}