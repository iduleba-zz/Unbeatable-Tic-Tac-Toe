#include "node.h"

NODE *newNode(NODE *parent, char player, int n, int aux){
    int i, pos;
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->points = 0;
    if(parent == NULL){
        node->state = STATE_GAME_ON;
        node->free_slots = n*n;
        node->board = newBoard(n);
        node->nodes = (NODE **)malloc(node->free_slots * sizeof(NODE *));
        for (i=0; i < node->free_slots; i++){
            node->nodes[i] = newNode(node, PLAYER1, n, i);
        }
        return node;
    }

    node->board = newBoard(n);
    node->free_slots = parent->free_slots - 1;
    copyBoard(parent->board, node->board);

    pos = findFreePosNo(parent->board, aux);
    setPosition(node->board, player, pos%n, pos/n);
    node->state = state(node->board);

    if (node->free_slots > 0){
        node->nodes = (NODE **)malloc(node->free_slots * sizeof(NODE *));
        for (i = 0; i < node->free_slots; i++){
            node->nodes[i] = newNode(node, (player == PLAYER1) ? PLAYER2 : PLAYER1, n, i);
        }
    }
    return node;
}

void deleteNode(NODE *node){
    if(node == NULL) return;
    int i;
    for (i = 0; i < node->free_slots; i++){
        deleteNode(node->nodes[i]);
    }
    if(node->free_slots > 0) free(node->nodes);
    deleteBoard(node->board);
    free(node);
}

void printNode(NODE *node){
    if (node == NULL) return;
    printBoard(node->board);
    int i;
    for (i = 0; i < node->free_slots; i++){
        printNode(node->nodes[i]);
    }
}