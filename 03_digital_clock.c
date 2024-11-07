#include <stdio.h>
#include <time.h>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif


void real_time(char*,int);
void real_date(char*);

int main(){
    int formate;
    char time_string[50];
    char date_string[50];

    printf("Enter the formate in which you want to see the time --\n");
    printf("1. 24 hour format\n");
    printf("2. 12 hour format(Default)\n");
    printf("Enter your choice:\n");
    scanf("%d",&formate);

    while (1)
    {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        real_time(time_string,formate);
        real_date(date_string);

        printf("Current Time: %s\n",time_string);
        printf("Date: %s\n",date_string);
        
        #ifdef _WIN32
            Sleep(1000);
        #else
            sleep(1);
        #endif
    }
    
    return 0;
}

// https://en.cppreference.com/w/cpp/chrono/c/strftime

void real_time(char* buffer,int formate){
    time_t t;
    struct tm* current_time;
    

    time(&t);
    current_time= localtime(&t);

    if (formate==1)
    {
        strftime(buffer,50,"%H:%M:%S",current_time);
    }else{
        strftime(buffer,50,"%I:%M:%S %p",current_time);
    }
    
}

void real_date(char* buffer){
    time_t d;
    struct tm* current_date;

    time(&d);
    current_date= localtime(&d);

        strftime(buffer,50,"%A %B %d %y",current_date);
    
}