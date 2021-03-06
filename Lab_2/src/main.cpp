#include "FileManager.h"

const char *HELP_FLAG = "-h";
const char *MOVE_FLAG = "-mv";
const char *DELETE_FLAG = "-dl";
const char *COPY_FLAG = "-cp";
const char *LS_FLAG = "-ls";
const char *SZ_FLAG = "-sz";
const char *PROC_FLAG = "-pinf";

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
        if (strcmp(flag, HELP_FLAG) == 0)
        {
            std::cout << "Авторы (ИС-841): Шамбуров Михаил\n"
                      << "Аргументы:\n"
                      << "1) -mv <oldName> <newName> - перемещает файл из oldName в newName\n"
                      << "Пример: ./file_manager -mv code.cpp src/code.cpp\n"
                      << "2) -dl <fileName> - удаляет файл fileName\n"
                      << "Пример: ./file_manager -dl src/code.cpp\n"
                      << "3) -cp <fileName> <destionation> - копирует файл fileName в destionation\n"
                      << "Пример: ./file_manager -cp src/code.cpp ../code.cpp\n"
                      << "4) -ls <fileName> - показывает содержимое каталога fileName\n"
                      << "Пример: ./file_manager -ls src/\n"
                      << "3) -sz <fileName> - показывае размер файла или каталога fileName\n"
                      << "Пример: ./file_manager -sz src/\n"
                      << "3) -pinf - показывает информацию о процессах из procfs\n"
                      << "Пример: ./file_manager -pinf\n";
            continue;
        }
        if (strcmp(flag, MOVE_FLAG) == 0)
        {
            if (argc < i + 2) // 2 означает, что присутствуют стрый путь и новый
                std::cout << "Ошибка! Недостаточно аргументов для флага " << MOVE_FLAG << std::endl;
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
        if (strcmp(flag, SZ_FLAG) == 0)
        {
            if (argc < i + 1)
                std::cout << "Ошибка! Недостаточно аргументов для флага " << SZ_FLAG << std::endl;
            else
            {
                try
                {
                    std::cout << FileManager::size(argv[i + 1]) << " byte\n";
                }
                catch (std::string error)
                {
                    std::cout << error << std::endl;
                }
                ++i;
            }
            continue;
        }
        if (strcmp(flag, PROC_FLAG) == 0)
        {
            try
            {
                FileManager::showProcfsProcesses();
            }
            catch (std::string error)
            {
                std::cout << error << std::endl;
            }
            continue;
        }
        std::cout << "Ошибка! Неизвестный флаг " << flag << std::endl;
    }
    return 0;
}