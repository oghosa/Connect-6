/*
 Name: Oghosa Igbinakenzua
 Student ID: 1000363590
 Course Code: APS105
 */
//***This program plays a smart game of connect 6.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "lab7_gfx.h"//////////////////

char winningStone = 'N';
int bestrow, bestcol;

//Prints Current Board.
void printBoard(char **board, int n)
{
    for (int i=0; i < n ; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != 'B' && board[i][j] != 'W')
            {
                board[i][j] = 'U';
            }
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

//Checks if spot is taken.
bool isTaken(char **board, int row, int col)
{
    if(board[row][col] == 'B' || board[row][col] == 'W')
        return true;
    return false;
}

int findLongest(char **board, int n, int row, int col)
{
    int countLongest;
    
    //Checks vertical
    int countvert = 0;
    for (int i = 1; ((row+i) < n) && (board[row+i][col] == board[row][col]) ; i++)  //UP
        countvert++;
    for (int i = 0; ((row-i) >= 0) && (board[row-i][col] == board[row][col]) ; i++) //DOWN
        countvert++;
    
    //Checks horizontal
    int counthorz = 0;
    for (int i = 1; ((col+i) < n) && (board[row][col+i] == board[row][col]) ; i++)  //RIGHT
        counthorz++;
    for (int i = 0; ((col-i) >= 0) && (board[row][col-i] == board[row][col]) ; i++) //LEFT
        counthorz++;
    
    //Checks Postive Diagonal
    int countPdiag = 0;
    for (int i = 1; ((col+i) < n) && ((row-i) >= 0) && (board[row-i][col+i] == board[row][col]) ; i++)  //UP RIGHT
        countPdiag++;
    for (int i= 0; ((col-i) >= 0) && ((row+i) < n) && (board[row+i][col-i] == board[row][col]) ; i++)   //DOWN LEFT
        countPdiag++;
    
    //Checks Negative Diagonal
    int countNdiag = 0;
    for (int i = 1; ((col-i) >= 0) && ((row-i) >= 0) && (board[row-i][col-i] == board[row][col]) ; i++) //UP LEFT
        countNdiag++;
    for (int i= 0; ((row+i) < n) && ((col+i) < n) && (board[row+i][col+i] == board[row][col]) ; i++)    //DOWN RIGHT
        countNdiag++;
    
    
    int strtTemp, diagTemp;
    
    //Compares straights
    if (countvert >= counthorz)
        strtTemp = countvert;
    else
        strtTemp = counthorz;
    
    //Compares diagonals
    if (countPdiag >= countNdiag)
        diagTemp = countPdiag;
    else
        diagTemp = countNdiag;
    
    //Compares straight against diagonals
    if (strtTemp > diagTemp)
        countLongest = strtTemp;
    else
        countLongest = diagTemp;
    
    return countLongest;
}


bool winnerCheck(char **board, int size)
{
    bool winner = false;
    for (int i=0; (i < size) && (winner == false); i++)
    {
        for (int j=0; (j < size) && (winner == false); j++)
        {
            if (isTaken(board, i, j))
            {
                if (findLongest(board, size, i, j) >= 6)
                {
                    if (board[i][j] == 'B')
                        winningStone = 'B';
                    else if (board[i][j] == 'W')
                        winningStone = 'W';
                    winner = true;
                    return true;
                }
            }
        }
    }
    return false;
}


int computerMove(char **board, int size, char stone, int layer)
{
    int max = -10000, temp;
    char humnStone, compStone;
    
    compStone = stone;
    
    if (compStone == 'B')
        humnStone = 'W';
    if (compStone == 'W')
        humnStone = 'B';
    
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            if (isTaken(board, i, j)==false)
            {
                board[i][j] = compStone;
                temp = findLongest(board, size, i, j);
                if (layer < 1)
                    temp -= computerMove(board, size, humnStone, layer+1);
                if (temp > max)
                {
                    max = temp;
                    bestrow = i;
                    bestcol = j;
                }
                board[i][j] = 'U';
            }
        }
    }
    
    return max;
}

bool isSixPossible(char **board, int size, char stone)
{
    bool SIX = false;
    for (int i=0; (i < size) && (SIX == false); i++)
    {
        for (int j=0; (j < size) && (SIX == false); j++)
        {
            if (isTaken(board, i, j) == false)
            {
                board[i][j] = stone;
                if (findLongest(board, size, i, j) >= 6)
                {
                    bestrow = i;
                    bestcol = j;
                    board[i][j] = 'U';
                    SIX = true;
                    return true;
                }
                board[i][j] = 'U';
            }
        }
    }
    return false;
}

int main()
{
	//initLab7Gfx();////////////////////////////////////////////////////////
    char **board;
    char compStone, humnstone;
    int size, humnrow, humncol;
    int playcount= 0;
    
    
    printf("Enter board dimensions (n): ");                     //Recives board dimension.
    scanf("%d", &size);
    
    //Creates board.
    board = (char **)malloc(sizeof(char *) * size);             //Allocates row of piointers
    for (int i=0; i < size; i++)
        board[i] = (char *)malloc(sizeof(char) * size);         //Allocates 'columns'
    
    printBoard(board, size);                                    //Initial board print.
    //displayGameboard(board, size);//////////////////////////////////////////////////
    
    printf("Computer playing B or W?: \n");
    scanf(" %c", &compStone);
    
    //If computer is White.
    if (compStone == 'W')
    {
        humnstone = 'B';
        printf("Lay down a stone (ROW COL): ");
        scanf("%d %d" ,&humnrow, &humncol);
        board[humnrow][humncol] = humnstone;
        printBoard(board, size);
        //displayGameboard(board, size);//////////////////////////////////////////////////
        playcount++;
    }
    
    //Sets human to Whiite if computer is Black
    if (compStone == 'B')
        humnstone = 'W';
    
    //GAME PLAY
    do {
        if (isSixPossible(board, size, compStone) == false)
        {
            if (isSixPossible(board, size, humnstone) == false)
                computerMove(board, size, compStone, 0);
        }
        board[bestrow][bestcol] = compStone;
        printf("Computer lays a stone at ROW %d COL %d.\n", bestrow, bestcol);
        printBoard(board, size);
        //displayGameboard(board, size);//////////////////////////////////////////////////
        playcount++;
        
        if((playcount == size*size) || (winnerCheck(board, size) == true))
            break;
        
        printf("Lay down a stone (ROW COL): ");
        scanf("%d %d" ,&humnrow, &humncol);
        
        while (isTaken(board, humnrow, humncol))
        {
            printf("That square is occupied.\n");
            printf("Lay down a stone (ROW COL): ");
            scanf("%d %d" ,&humnrow, &humncol);
        }
        
        board[humnrow][humncol] = humnstone;
        printBoard(board, size);
        //displayGameboard(board, size);//////////////////////////////////////////////////
        playcount++;
        
    } while ((winnerCheck(board, size) == false) && (playcount < size*size));
    
    
    if (winningStone == 'B')
        printf("Black player wins.\n");
    if (winningStone == 'W')
        printf("White player wins.\n");
    if (winningStone == 'N')
        printf("Draw.\n");
    
    //closeLab7Gfx(); //////////////////////////////////////////////////
    return 0;
}
