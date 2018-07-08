# include "ai.h"

NODE *createTree(BOARD *board, char player){
    return newNode(NULL, player, board->n, 0);
}

void deleteTree(NODE *tree){
    deleteNode(tree);
}

void normalizeTreeAux(NODE *node, char player){
    int i, countVictories = 0, countDefeats = 0, countDraws = 0;
    for(i = 0; i < node->free_slots; i++){
        normalizeTreeAux(node->nodes[i], player);
        switch(node->nodes[i]->state) {
            case STATE_PLAYER1_WINS :
                if(player == PLAYER1){ countVictories++; }
                else{ countDefeats++; }
                break;
            case STATE_PLAYER2_WINS :
                if(player == PLAYER2){ countVictories++; }
                else{ countDefeats++; }
                break;
            case STATE_DRAW :
                countDraws++;
                break;
            default :
                break;
        }
    }
    if(countVictories == node->free_slots && countVictories > 0){
        if(player == PLAYER1){
            node->state = STATE_PLAYER1_WINS;
        }else{
            node->state = STATE_PLAYER2_WINS;
        }
    }else if(countDraws == node->free_slots && countDraws > 0){
        node->state = STATE_DRAW;
    }else if(countDefeats == node->free_slots && countDefeats > 0){
        if(player == PLAYER1){
            node->state = STATE_PLAYER2_WINS;
        }else{
            node->state = STATE_PLAYER1_WINS;
        }
    }
}

void normalizeTree(NODE *tree, char player){
    int i;
    for(i = 0; i < tree->free_slots; i++){
        normalizeTreeAux(tree->nodes[i], player);
    }
}

int chooseNextMove(NODE **currentNode, char player){
    int i;
    for(i = 0; i < (*currentNode)->free_slots; i++){
        if((*currentNode)->nodes[i] != NULL
        && (*currentNode)->nodes[i]->state == ((player == PLAYER1) ? STATE_PLAYER1_WINS : STATE_PLAYER2_WINS)){
            int ret = diff((*currentNode)->board, (*currentNode)->nodes[i]->board);
            printf("currentNode: \n");
            printBoard((*currentNode)->board);
            printf("currentNode son (Win %d %c): \n", (*currentNode)->nodes[i]->state, player);
            printBoard((*currentNode)->nodes[i]->board);
            *currentNode = (*currentNode)->nodes[i];
            return ret;
        }
    }
    for(i = 0; i < (*currentNode)->free_slots; i++){
        if((*currentNode)->nodes[i] != NULL
        && (*currentNode)->nodes[i]->state != ((player == PLAYER1) ? STATE_PLAYER2_WINS : STATE_PLAYER1_WINS)){
            int ret = diff((*currentNode)->board, (*currentNode)->nodes[i]->board);
            printf("currentNode: \n");
            printBoard((*currentNode)->board);
            printf("currentNode son (GameON %d %c): \n", (*currentNode)->nodes[i]->state, player);
            printBoard((*currentNode)->nodes[i]->board);
            *currentNode = (*currentNode)->nodes[i];
            return ret;
        }
    }
    return -1;
}

void updateCurrentNode(BOARD *board, NODE **currentNode){
    int i;
    for(i = 0; i < (*currentNode)->free_slots; i++){
        if((*currentNode)->nodes[i] != NULL){
            if(diff(board, (*currentNode)->nodes[i]->board) == FALSE){
                *currentNode = (*currentNode)->nodes[i];
                return;
            }
        }
    }
}
