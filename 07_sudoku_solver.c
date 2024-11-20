#include <stdio.h>
#include <windows.h>

int puzzle_01[9][9] = {
    {4,0,0,0,3,0,0,0,0},
    {0,7,0,0,0,0,0,0,0},
    {0,0,0,5,8,1,0,0,4},
    {0,0,0,0,0,0,0,2,0},
    {0,0,0,8,4,0,0,0,3},
    {2,0,1,0,0,0,8,0,0},
    {0,0,5,9,0,0,0,0,0},
    {6,0,0,4,1,8,0,0,0},
    {0,1,0,0,0,5,2,7,0}
};

void print_puzzle(int puzzle[9][9]);
int valid_puzzle(int puzzle[9][9], int row,int col,int val);
int solve_puzzle(int puzzle[9][9], int row,int col);

int main(){
    system("cls");
    printf("\n\t=======WELCOME TO SUDOKU PUZZLE SOLVER=======");
    printf("\nSudoku Puzzle:\n");

    print_puzzle(puzzle_01);
    
    if (solve_puzzle(puzzle_01,0,0))
    {
        printf("---------------------------------------------");
        printf("\nPuzzle solved");
        print_puzzle(puzzle_01);
    }
    

    return 0;
}

int solve_puzzle(int puzzle[9][9], int row,int col){
    if (col==9)
    {
        if (row==8)
        {
            return 1;
        }
        row++;
        col = 0;
    }

    if (puzzle[row][col]>0)
    {
        return solve_puzzle(puzzle,row,col+1);
    }
    
    for (int i = 1; i < 10; i++)
    {
        if (valid_puzzle(puzzle,row,col,i))     
        {
            puzzle[row][col]=i;
            if (solve_puzzle(puzzle,row,col+1))
            {
                return 1;
            }else{
                puzzle[row][col]=0;
            }
            
        }
        
    }
    return 0;
    
}

int valid_puzzle(int puzzle[9][9], int row,int col,int val){
    // Check row
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == val)
        {
            return 0;
        }
        
    }

    // Check col
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[i][col] == val)
        {
            return 0;
        }
        
    }

    // Check square
    int r = row - (row % 3);
    int c = col - (col % 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[r+i][c+j] == val)
            {
                return 0;
            }
            
        }
        
    }
    
    return 1;
    
}

void print_puzzle(int puzzle[9][9]){

    printf("\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++)
    {
        if (row%3 == 0 && row!=0){
            printf("\n+-------+-------+-------+");
        }
        printf("\n");
        for (int col = 0; col < 9; col++)
        {
            if (col%3 == 0)
            {
                printf("| ");
            }
            
            if (puzzle[row][col]!=0)
            {
                printf("%d ",puzzle[row][col]);
            }else{
                printf("  ");
            }
            
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
    
}