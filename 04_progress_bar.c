#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

const int MAX_LENGTH = 30;
int number_of_tasks = 5;

typedef struct
{
    int id;
    int progress;
    int step;
} Task;
void print_bar(Task task);

int main()
{
    srand(time(NULL));
    int not_complete = 1;
    Task task[10];

    for (int i = 0; i < number_of_tasks; i++)
    {
        task[i].id = i + 1;
        task[i].progress = 0;
        task[i].step = (rand() % 4) + 1;
    }

    while (not_complete)
    {
        not_complete=0;
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        for (int j = 0; j < number_of_tasks; j++)
        {
            task[j].progress += task[j].step;

            if (task[j].progress > 100) {
                task[j].progress = 100;
            }else if(task[j].progress<100){
                not_complete=1;
            }
            print_bar(task[j]);
        }
        
        #ifdef _WIN32
                Sleep(1000);
        #else
                sleep(1);
        #endif
    }

    printf("All tasks are completed!\n");

    return 0;
}

void print_bar(Task task)
{
    printf("Task %d :[", task.id);
    int bars_to_show = (MAX_LENGTH * task.progress) / 100;

    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if (i < bars_to_show)
        {
            printf("=");
        }
        else
        {
            printf(" ");
        }
    }

    printf("] %d%%\n", task.progress);
}