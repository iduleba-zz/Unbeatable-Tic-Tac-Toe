# include "ai.h"

NODE *createTree(BOARD *board, char player, int pos){
    if(player ==  PLAYER1){
        return newNode(NULL, player, board->n, 0);
    }
    return newNode(NULL, player, board->n, pos);
}

void deleteTree(NODE *tree){
    deleteNode(tree);
}

void normalizeTreeAux(NODE *node, char player){
    int i;
    if(player == PLAYER1){
        if(node->state == STATE_PLAYER2_WINS){
            deleteNode(node);
            node = NULL;
        }else if(node->state == STATE_GAME_ON){
            for(i = 0; i < node->free_slots; i++){
                normalizeTreeAux(node->nodes[i], player);
            }
            int count = 0;
            for(i = 0; i < node->free_slots; i++){
                if(node->nodes[i] != NULL) return;
                count++;
            }
            if(count == node->free_slots - 1){
                deleteNode(node);
                node = NULL;
            }
        }
    }else if(player == PLAYER2){
        if(node->state == STATE_PLAYER1_WINS){
            deleteNode(node);
            node = NULL;
        }else if(node->state == STATE_GAME_ON){
            for(i = 0; i < node->free_slots; i++){
                normalizeTreeAux(node->nodes[i], player);
            }
            int count = 0;
            for(i = 0; i < node->free_slots; i++){
                if(node->nodes[i] != NULL) return;
                count++;
            }
            if(count == node->free_slots - 1){
                deleteNode(node);
                node = NULL;
            }
        }
    }
}

void normalizeTree(NODE *tree, char player){
    int i;
    for(i = 0; i < tree->free_slots; i++){
        normalizeTreeAux(tree->nodes[i], player);
    }
}

int chooseNextMove(NODE **currentNode){
    int i;
    for(i = 0; i < (*currentNode)->free_slots; i++){
        if((*currentNode)->nodes[i] != NULL){
            int ret = diff((*currentNode)->board, (*currentNode)->nodes[i]->board);
            printBoard((*currentNode)->nodes[i]->board);
            printBoard((*currentNode)->board);
            *currentNode = (*currentNode)->nodes[i];
            return ret;
        }
    }
    return -1;
}
