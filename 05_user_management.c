#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX_USER 10

void registration(char*,char*);
void login();
void get_password(char*);

typedef struct 
{
    char username[30];
    char password[15];
}sUser;
sUser user[MAX_USER];

int user_count = 0;

int main(){
    while (1)
    {
        int option;

        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        getchar(); 

        switch (option)
        {
        case 1:
            if(user_count<MAX_USER){
                printf("---------------------------------\n");
                printf("Registration Form\n");
                
                registration(user[user_count].username,user[user_count].password);
            }else{
                printf("Maximum user reached\n");
            }
            break;
        case 2:
            printf("---------------------------------\n");
            printf("Login user\n");
            login();
            break;
        case 3:
            return 0;

        default:
        printf("Please enter a correct option\n");
            break;
        }

    }
    
}

void registration(char* dUsername, char* dpassword){
    char username[20], password[20], confirm_password[20];
    int U_N_exist;

    do
    {
        U_N_exist=0;
        printf("Enter a username: ");
        fgets(username,sizeof(username),stdin);
        username[strcspn(username, "\n")] = '\0';

        for (int j = 0; j < MAX_USER; j++)
        {
            if(strcmp(user[j].username,username)==0){
                printf("\nUsername already exists\n");
                U_N_exist=1;
                break;
            }
        }

    }while(U_N_exist);

    printf("\nEnter a password: ");
    get_password(password);

    while (1)
    {
        printf("\nConfirm your password: ");
        get_password(confirm_password);

        if (strcmp(password, confirm_password) == 0){
            strcpy(dUsername, username);
            strcpy(dpassword, password);
            printf("\nRegistration successful\n");
            user_count++;
            break;
        }else{
            printf("Passwords do not match!!\n");
        }
    }
    printf("---------------------------------\n");
}

void login(){
    char username[20], password[20];
    int login_unsuccess = 1;

    printf("\nEnter your username: ");
    fgets(username,sizeof(username),stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("\nEnter your password: ");
    get_password(password);

    for (int j = 0; j < MAX_USER; j++)
    {
        if(strcmp(user[j].username,username)==0 && strcmp(user[j].password,password)==0){
            printf("\nLogin successful\n");
            login_unsuccess = 0;
            break;
        }
    }

    if (login_unsuccess)
    {
        printf("\nLogin failed. Incorrect username or password!!\n");
    }
    printf("---------------------------------\n");
}

void get_password(char* password){
    int index=0;
    char ch;
    while ((ch=_getch())!='\r')
    {
        if(ch=='\b' && index > 0){
            printf("\b \b");
            index--;
        }else if (ch != '\b' && index < 14)
        {
            password[index++]=ch;
            printf("*");
        }
        
    }
    password[index]='\0';
    printf("\n");
}