#include "board.h"

BOARD *newBoard(int n){
    BOARD *board = (BOARD *) malloc(sizeof(BOARD));
    board->n = n;
    board->board = (char *) malloc(n*n*sizeof(char));
    cleanBoard(board);
    return board;
}

void deleteBoard(BOARD *board){
    free(board->board);
    free(board);
}

void cleanBoard(BOARD *board){
    int i;
    for(i = 0; i < board->n * board->n; i++){
        board->board[i] = ' ';
    }
}

void printBoard(BOARD *board){
    int i, j;
    printf("\n");
    for(i = 0; i < board->n; i++){
        for(j = 0; j < board->n - 1; j++){
            printf("%c | ",board->board[i*board->n + j]);
        }
        printf("%c\n",board->board[i*board->n + board->n - 1]);
        if(i < board->n - 1){
            for(j = 0; j < board->n; j++){
                printf("---");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void copyBoard(BOARD *oldBoard, BOARD *board){
    int i;
    board->n = oldBoard->n;
    for (i = 0; i < board->n * board->n; i++){
        board->board[i] = oldBoard->board[i];
    }
}

int pos(int n, int x, int y){
    if (x < n && x >= 0 && y < n && y >= 0){
        return y*n + x;
    }
    return ERR_POSITION_OUT_OF_BOUNDS;
}

int findFreePosNo(BOARD *board, int aux){
    int i, count = 0;
    for(i = 0; i < board->n * board->n ; i++){
        if(board->board[i] == ' '){
            if(count == aux) return i;
            count++;
        }
    }
    return -1;
}

int setPosition(BOARD *board, char player, int x, int y){
    if (player != PLAYER1 && player != PLAYER2) return ERR_PLAYER_UNDEFINED;
    if (board == NULL || board->board == NULL) return ERR_MEM;

    int position = pos(board->n, x, y);
    if (position == ERR_POSITION_OUT_OF_BOUNDS) return ERR_POSITION_OUT_OF_BOUNDS;
    if (board->board[position] != ' ') return ERR_POSITION_OCCUPIED;
    
    board->board[position] = player;
    return TRUE;
}

int isComplete(BOARD *board){
    int i, j, n;
    n = board->n;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if(board->board[i*n + j] != PLAYER1 && board->board[i*n + j] != PLAYER2) return FALSE;
        }
    }
    return TRUE;
}

char checkRows(BOARD *board){
    int i, j, n, p1 = 0, p2 = 0;
    n = board->n;
    for (i = 0; i < n; i++){
        p1 = 0; p2 = 0;
        for (j = 0; j < n; j++){
            if(board->board[i*n + j] == PLAYER1) p1++;
            if(board->board[i*n + j] == PLAYER2) p2++;
        }
        if(p1 == n) return PLAYER1;
        if(p2 == n) return PLAYER2;
    }
    return ' ';
}

char checkColumns(BOARD *board){
    int i, j, n, p1 = 0, p2 = 0;
    n = board->n;
    for (j = 0; j < n; j++){
        p1 = 0; p2 = 0;
        for (i = 0; i < n; i++){
            if(board->board[i*n + j] == PLAYER1) p1++;
            if(board->board[i*n + j] == PLAYER2) p2++;
        }
        if(p1 == n) return PLAYER1;
        if(p2 == n) return PLAYER2;
    }
    return ' ';
}

char checkDiagonals(BOARD *board){
    int i, n, p1 = 0, p2 = 0;
    n = board->n;

    for (i = 0; i < n; i++){
        if(board->board[i*n + i] == PLAYER1) p1++;
        if(board->board[i*n + i] == PLAYER2) p2++;
    }
    if(p1 == n) return PLAYER1;
    if(p2 == n) return PLAYER2;

    p1 = 0; p2 = 0;
    for (i = 0; i < n; i++){
        if(board->board[(n-1)*i] == PLAYER1) p1++;
        if(board->board[i*n + i] == PLAYER2) p2++;
    }
    if(p1 == n) return PLAYER1;
    if(p2 == n) return PLAYER2;
    return ' ';
}

int state(BOARD *board){
    if (board == NULL || board->board == NULL) return ERR_MEM;
    
    char rows = checkRows(board);
    char columns = checkColumns(board);
    char diagonals = checkDiagonals(board);
    if (rows == PLAYER1 || columns == PLAYER1 || diagonals == PLAYER1) return STATE_PLAYER1_WINS;
    if (rows == PLAYER2 || columns == PLAYER2 || diagonals == PLAYER2) return STATE_PLAYER2_WINS;
    if (isComplete(board) == TRUE) return STATE_DRAW;
    return STATE_GAME_ON;
}

int diff(BOARD *board1, BOARD *board2){
    if(board1 == NULL || board2 == NULL) return ERR_MEM;
    int i;
    for(i = 0; i < board1->n * board1->n; i++){
        if(board1->board[i] != board2->board[i]) return i;
    }
    return FALSE;
}