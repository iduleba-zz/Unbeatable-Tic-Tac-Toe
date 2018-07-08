#include "board.h"
#include "ai.h"

void printMenu(){
    printf("Welcome! Do you want to play TIC TAC TOE:\n");
    printf("1) Against an AI\n or\n2) Against another player?\n");
    printf("Option: ");
}

void printSubMenu(){
    printf("Do you wanna go first? (y/n) ");
}

void readPosition(int *x, int *y, char player){
    printf("Player %c: (x y coordinates) ", player);
    scanf("%d %d", x, y);
}

void humanPlay(BOARD *board, char player){
    int x, y;
    int set = FALSE;
    while(set != TRUE){
        readPosition(&x, &y, player);
        set = setPosition(board, player, x, y);
        switch(set) {
            case ERR_PLAYER_UNDEFINED :
                printf("Wrong Player!\n");
                break;
            case ERR_MEM :
                printf("Mem err!\n");
                break;
            case ERR_POSITION_OUT_OF_BOUNDS :
                printf("Invalid Position!\n" );
                break;
            case ERR_POSITION_OCCUPIED :
                printf("Position already occupied!\n" );
                break;
            case TRUE:
                break;
            default :
                printf("Invalid error!\n");
        }
    }
}

int firstRound(BOARD *board){
    int i;
    for(i = 0; i < board->n * board->n; i++){
        if(board->board[i] == PLAYER1) return i;
    }
    return -1;
}

void aiPlay(BOARD *board, char player, NODE **tree, NODE **currentNode){
    if(*tree == NULL){
        printf("TREE NULL\n");
        *tree = createTree(board, player);
        normalizeTree(*tree, player);
        *currentNode = *tree;
    }

    updateCurrentNode(board, currentNode);
    
    int pos = chooseNextMove(currentNode, player);
    if(pos == -1){
        printf("You have beaten me? How?\n");
    }
    setPosition(board, player, pos%board->n, pos/board->n);
}

int main(int argc, char **argv){
    Start:
        printMenu();
        int option; // 1 is against AI; 2 against an opponent
        scanf("%d", &option);

        if(option != 1 && option != 2){
            printf("Moron.\n");
            return -1;
        }

        NODE *tree = NULL, *currentNode = NULL;
        char first = ' ';
        if(option == 1){
            printSubMenu();
            scanf(" %c", &first);

            if(first == 'y' || first == 'Y'){
                option = 0;
            }else if(first == 'n' || first == 'N'){
                option = 1;
            }else{
                printf("Moron.\n");
                return -1;
            }

        }

        BOARD *board = newBoard(3);

        char player = PLAYER1;
        int ai = option;

        while(state(board) == STATE_GAME_ON){
            if(ai == 0){//human to play
                humanPlay(board, player);
            }else{//machine to play
                aiPlay(board, player, &tree, &currentNode);
            }
            printBoard(board);
            //change player
            if(option != 2) ai = (ai == 0) ? 1 : 0; // if we are playing against the computer, alternate btween human an computer
            if(player == PLAYER1) player = PLAYER2;
            else if(player == PLAYER2) player = PLAYER1;
            else return -1;
        }

        switch(state(board)) {
            case STATE_PLAYER1_WINS :
                printf("Player %c wins!\n", PLAYER1);
                break;
            case STATE_PLAYER2_WINS :
                printf("Player %c wins!\n", PLAYER2);
                break;
            case STATE_DRAW :
                printf("Draw!\n" );
                break;
            default :
                printf("Invalid state!\n");
        }

        deleteBoard(board);
        if(option != 2) deleteTree(tree);

        printf("Wanna go again? (y/n) ");
        scanf(" %c", &first);
        if(first == 'y' || first == 'Y'){
            goto Start;
        }else if(first == 'n' || first == 'N'){
            printf("Thanks for playing!");
            return 0;
        }else{
            printf("Moron.\n");
            return -1;
        }
}