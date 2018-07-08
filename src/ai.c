# include "ai.h"

NODE *createTree(BOARD *board, char player){
    return newNode(NULL, player, board->n, 0);
}

void deleteTree(NODE *tree){
    deleteNode(tree);
}

//minmax logic
int normalizeTreeAux(NODE *node, char player){
    int i;
    int value = 0;
    int min = -1;
    int max = 1;
    switch(node->state) {
        case STATE_PLAYER1_WINS :
            if(player == PLAYER1){ node->points = 10; }
            else{ node->points = -10; }
            return node->points;
        case STATE_PLAYER2_WINS :
            if(player == PLAYER2){ node->points = 10; }
            else{ node->points = -10; }
            return node->points;
        case STATE_DRAW :
            return 0;
        default:
            for(i = 0; i < node->free_slots; i++){
                //TODO
                value = normalizeTreeAux(node->nodes[i], player);
                if(value == -10){
                    min = -10;
                }else if(value == 10){
                    max = 10;
                }
            }
    }
}

void normalizeTree(NODE *tree, char player){
    normalizeTreeAux(tree, player);
}

int chooseNextMove(NODE **currentNode, char player){
    int i, iMax=-1, aux = -1000;
    for(i = 0; i < (*currentNode)->free_slots; i++){
        if((*currentNode)->nodes[i] != NULL && (*currentNode)->nodes[i]->points > aux){
            aux = (*currentNode)->nodes[i]->points;
            iMax = i;
        }
    }
    if(iMax != -1){
            int ret = diff((*currentNode)->board, (*currentNode)->nodes[iMax]->board);
            *currentNode = (*currentNode)->nodes[iMax];
            return ret;
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
