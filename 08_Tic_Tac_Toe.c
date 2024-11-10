#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 3

typedef struct{
    int player;
    int computer;
    int draw;
}Score;

int option;
char name[20];
Score score={.player = 0, .computer = 0, .draw  = 0};

void input_difficulty();
void score_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE],char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
void clear_screen();

int main(){
    int choice;
    srand(time(NULL));

    printf("\nEnter your name: ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]='\0';
    printf("\n***** Welcome %s *****",name);

    do{
        input_difficulty();
        play_game();
        printf("\nDo you want to play again?(1 for yes And 0 for no): ");
        scanf("%d",&choice);
    }while(choice==1);
    system("color 7");
    printf("\nThank you for playing!!\n");

    return 0;
}

void play_game(){
    char board[BOARD_SIZE][BOARD_SIZE]={
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };

    char current_player = rand() % 2 == 0 ? 'X' : 'O';

    score_board(board);
    while(1){
        
        

        if (current_player == 'X')
        {
            player_move(board);
            score_board(board);
            if (check_win(board, 'X'))
            {
                score.player++;
                score_board(board);
                system("color 2");
                printf("\nCongratulations, %s , You have won!!\n", name);
                break;
            }
            current_player = 'O';
            
        }else{
            computer_move(board);
            score_board(board);
            if (check_win(board, 'O'))
            {
                score.computer++;
                score_board(board);
                system("color 4");
                printf("\nI won! But you played well, %s.\n", name);
                break;
            }
            current_player = 'X';
        }

        if (check_draw(board))
        {
            score.draw++;
            score_board(board);
            printf("\nIt's a draw!");
            break;
        }

    }

}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col){
    return !(row<0 || row>2 || col<0 || col>2 || board[row][col]!=' ');
}
        

void player_move(char board[BOARD_SIZE][BOARD_SIZE]){
    int count = 0, x , y;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                count++;
                x = i;
                y = j;
            }
            
        }
        
    }

    if (count == 1)
    {
        board[x][y] = 'X';
        return;
    }

    int row, col;
    do{
        printf("\nYour turn:");
        printf("\nEnter row and column (1 - 3) for X: ");
        scanf("%d %d",&row,&col);
        row--; col--;
    }while(! is_valid_move(board,row,col));

    board[row][col]='X';

    return;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]){
    // 1. Check imidiate win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j]='O';
                if (check_win(board,'O'))
                {
                    return;
                }
                board[i][j]=' ';
            }
            
        }
        
    }

    // 2. Check imidiate block
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j]='X';
                if (check_win(board,'X'))
                {   
                    board[i][j]='O';
                    return;
                }
                board[i][j]=' ';
            }
            
        }
        
    }

    // GOD mode
    if (option == 2)
    {
        // 3. Capture center
        if (board[1][1] == ' ')
        {
            board[1][1]='O';
            return;
        }

        // 4. Cpature cornar
        int cornar[4][2]={
            {0,0},
            {0,2},
            {2,0},
            {2,2}
        };
        for (int i = 0; i < 4; i++)
        {
            if (board[cornar[i][0]][cornar[i][1]] == ' ')
            {
                board[cornar[i][0]][cornar[i][1]] = 'O';
                return;
            }
            
        }
        
    }
    
    // 5. play at any point
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j]='O';
                return;
            }
            
        }
        
    }
}

void input_difficulty(){
    while (1)
    {
        printf("\nSelect defficulty level: ");
        printf("\n1. Human(Standard)");
        printf("\n2. God(Impossible to win)");
        printf("\nEnter your choice: ");
        scanf("%d",&option);
        if (option!=1 && option!=2)
        {
            printf("\nIncorrect choice.Please enter (1/2)!!");
        }else{
            break;
        }       
    }
}

void score_board(char board[BOARD_SIZE][BOARD_SIZE]){
    clear_screen();
    printf("\nScore:- \n\t%s: %d \n\tComputer:%d \n\tDraw:%d",name,score.player,score.computer,score.draw);
    printf("\nTic-Tac-Toe\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ",board[i][j]);
            if (j < BOARD_SIZE-1)
            {
                printf("|");
            }
        }
        if (i < BOARD_SIZE-1)
        {
            printf("\n---+---+---");
        }
        
    }
    printf("\n");
    
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Check rows
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1;
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++){
        // Check columns
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return 1;
        }
    }
    
    // Check diagonal
    if((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player)){
        return 1;
    }
    
    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == ' '){
                return 0;
            }    
        }
    }
    return 1;
}

void clear_screen(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}