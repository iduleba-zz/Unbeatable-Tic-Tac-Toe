# include "ai.h"

NODE *createTree(BOARD *board, char player){
    return newNode(NULL, player, board->n, 0);
}

void deleteTree(NODE *tree){
    deleteNode(tree);
}

//minmax logic
int normalizeTreeAux(NODE *node, char player, int minMax){
    int i;
    int value = 0;
    int min = 10;
    int max = -10;
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
                value = normalizeTreeAux(node->nodes[i], player, (minMax == 0) ? 1 : 0);
                if(value < min){
                    min = value;
                }
                if(value > max){
                    max = value;
                }
            }
            node->points = (minMax == 0) ? min : max;
            return node->points;
    }
}

void normalizeTree(NODE *tree, char player){
    int i, value;
    for(i = 0; i < tree->free_slots; i++){
        value = normalizeTreeAux(tree->nodes[i], player, 0);
    }
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
