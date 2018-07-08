#ifndef _NODE
#define _NODE

#include "board.h"

typedef struct NODE NODE;

struct NODE{
    BOARD *board;
    NODE **nodes;
    int free_slots;
    int state;
    int points;
};

NODE *newNode(NODE *parent, char player, int n, int count);
void deleteNode(NODE *node);
void printNode(NODE *node);

#endif //end of _NODE