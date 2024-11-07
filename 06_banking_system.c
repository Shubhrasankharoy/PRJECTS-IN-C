#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void create_acc();
void diposit_money();
void withdraw_money();
void display_balance();
int create_acc_num();

const char* file_name = "account.dat";

typedef struct 
{
    char name[20];
    int phone_number;
    float balance;
    int account_number;
}account;


int main(){
    system("color 9");
    int option;

    while (1)
    {
        printf("\n---------------------------");
        printf("\n**WELCOME TO BHAARATIYA BANK**");
        printf("\n1: Create account.");
        printf("\n2: Diposit money.");
        printf("\n3: Withdraw money.");
        printf("\n4: Check Ballance.");
        printf("\n5: Exit.\n");
        scanf("%d",&option);

        switch (option)
        {
        case 1:
            create_acc();
            break;
        case 2:
            diposit_money();
            break;
        case 3:
            withdraw_money();
            
            break;
        case 4:
            display_balance();
            break;
        case 5:
            return 0;
            break;
        
        default:
            printf("\nInvalid option!!");
            break;
        }
    }
}

void create_acc(){
    account acc_holder;
    FILE *file = fopen(file_name,"ab+");
    FILE *file1 = fopen("account_details.txt","a");

    if(file==NULL){
        printf("\nSurver Down. Please try again later!!");
        return;
    }

    // Clear all enters.
    char ch;
    do
    {
        ch=getchar();
    } while (ch!='\n');
      
    // Take required inputs from user.

    printf("\n---------------------------");
    printf("\nEnter your name: ");
    fgets(acc_holder.name,sizeof(acc_holder.name),stdin);
    acc_holder.name[strcspn(acc_holder.name,"\n")] = '\0';

    printf("\nEnter your mobile number: ");
    scanf("%d",&acc_holder.phone_number);
    
    acc_holder.balance=0.00;
    acc_holder.account_number=create_acc_num();

    // Check mobile number from data base


    // Save the detailes in data base
    fwrite(&acc_holder,sizeof(acc_holder),1,file);
    fprintf(file1, "%s %d\n",acc_holder.name, acc_holder.account_number);
    fclose(file);
    fclose(file1);

    // Responce msg
    printf("\nYour account is created successfully.");
    printf("\nYour account number is %d.", acc_holder.account_number);
    printf("\nYour current balance is %.2f", acc_holder.balance);
    
}

void diposit_money(){
    // open file
    FILE* file = fopen(file_name,"rb+");
    if (file==NULL)
    {
        printf("\nSurver Down. Please try again later!!");
        return;
    }

    //take required details to identify user
    int acc_num;
    printf("\nEnter your account number: ");
    scanf("%d",&acc_num);

    // Find user's detailes
    account acc_holder;
    while (fread(&acc_holder, sizeof(acc_holder),1,file))
    {
        if (acc_holder.account_number == acc_num  )
        {
            float amount;
            printf("\nEnter amount to deposit: ");
            scanf("%f",&amount);
            acc_holder.balance += amount;

            // Save the detailes in data base
            fseek(file,-sizeof(acc_holder),SEEK_CUR);
            fwrite(&acc_holder,sizeof(acc_holder),1,file);
            fclose(file);
            
            printf("\nSuccessfully withdrawn Rs. %.2f.New balance is Rs. %.2f",amount,acc_holder.balance);
            return;
        }
        
    }

    fclose(file);
    printf("\nYou have entered a wrong account number!!");
}

void withdraw_money(){
    // open file
    FILE* file = fopen(file_name,"rb+");
    if (file==NULL)
    {
        printf("\nSurver Down. Please try again later!!");
        return;
    }

    //take required details to identify user
    int acc_num;
    printf("\nEnter your account number: ");
    scanf("%d",&acc_num);

    // Find user's detailes
    account acc_holder;
    while (fread(&acc_holder, sizeof(acc_holder),1,file))
    {
        if (acc_holder.account_number == acc_num  )
        {
            float amount;
            Enter_amount:
                printf("\nEnter amount to withdraw: ");
                scanf("%f",&amount);
                if(amount<=acc_holder.balance){
                    acc_holder.balance -= amount;

                    // Save the detailes in data base
                    fseek(file,-sizeof(acc_holder),SEEK_CUR);
                    fwrite(&acc_holder,sizeof(acc_holder),1,file);
                    fclose(file);
                }else{
                    printf("\nInsufficient balance!!");
                    goto Enter_amount;
                }
            
            printf("\nSuccessfully deposited Rs. %.2f.New balance is Rs. %.2f",amount,acc_holder.balance);
            return;
        }
        
    }

    fclose(file);
    printf("\nYou have entered a wrong account number!!");
}

void display_balance(){
    // open file
    FILE* file = fopen(file_name,"rb");
    if (file==NULL)
    {
        printf("\nSurver Down. Please try again later!!");
        return;
    }
    
    //take required details to identify user
    int acc_num;
    printf("\nEnter your account number: ");
    scanf("%d",&acc_num);

    // Find user's detailes
    account acc_holder;
    while (fread(&acc_holder, sizeof(acc_holder),1,file))
    {
        if (acc_holder.account_number == acc_num  )
        {
            printf("\nYour current balance is Rs. %.2f",acc_holder.balance);
            fclose(file);
            return;
        }
        
    }

    fclose(file);
    printf("\nYou have entered a wrong account number!!");
    
}

int create_acc_num(){
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random number of 4 digits
    int acc_num = rand() % 9000 + 1000;

    return acc_num;
}