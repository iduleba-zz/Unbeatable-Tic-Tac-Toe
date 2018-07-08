#ifndef _AI
#define _AI

#include "node.h"

NODE *createTree(BOARD *board, char player, int pos);
void normalizeTree(NODE *tree, char player);
void deleteTree(NODE *tree);
int chooseNextMove(NODE **currentNode);

#endif //end of _AI