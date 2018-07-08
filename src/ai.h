#ifndef _AI
#define _AI

#include "node.h"

NODE *createTree(BOARD *board, char player);
void normalizeTree(NODE *tree, char player);
void deleteTree(NODE *tree);
void updateCurrentNode(BOARD *board, NODE **currentNode);
int chooseNextMove(NODE **currentNode, char player);

#endif //end of _AI