#ifndef _BOARD
#define _BOARD

#include <stdio.h>
#include <stdlib.h>

#define TRUE 0
#define FALSE -1

#define PLAYER1 'X'
#define PLAYER2 'O'

#define ERR_PLAYER_UNDEFINED -2
#define ERR_MEM -3
#define ERR_POSITION_OUT_OF_BOUNDS -4
#define ERR_POSITION_OCCUPIED -5

#define STATE_PLAYER1_WINS 100
#define STATE_PLAYER2_WINS 101
#define STATE_GAME_ON 102
#define STATE_DRAW 103



typedef struct BOARD{
    int n;
    char *board; // not very clever. I should use another data structure
}BOARD;

BOARD *newBoard(int n);
void deleteBoard(BOARD *board);
void cleanBoard(BOARD *board);
void printBoard(BOARD *board);
int setPosition(BOARD *board, char player, int x, int y);
int state(BOARD *board);
void copyBoard(BOARD *oldBoard, BOARD *board);
int findFreePosNo(BOARD *board, int aux);
int diff(BOARD *board1, BOARD *board2);

#endif //end of _BOARD