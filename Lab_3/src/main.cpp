#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

using namespace std;

const char *HELP_FL = "-h";
const char *EXECUTE_FL = "-exe";

void showInfo();
int executeProgramm();

int main(int argc, char *argv[])
{

    if (argc < 2)
        cout << "Слишком мало аргументов; -h за помощью\n";
    else
    {
        if (strcmp(argv[1], HELP_FL) == 0)
            showInfo();
        else if (strcmp(argv[1], EXECUTE_FL) == 0)
        {
            executeProgramm();
        }
        else
        {
            cout << "Неизвестный параметр " << argv[1] << "; -h за помощью\n";
        }
    }
    return 0;
}

void showInfo()
{
    cout << "Авторы (ИС-841): Шамбуров Михаил, Перов Артем\n";
    cout << "Параметры:\n";
    cout << "-exe <path> - программа, которая будет запускаться в дочернем процессе\n";
    cout << "Пример: ./LiteSH -exe ../bin/file_manager\n";
}

int executeProgramm()
{

}