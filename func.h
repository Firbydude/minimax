#ifndef FUNC_H
#define FUNC_H

#include <stdbool.h>

#define INFINITY 0x7FFFFFFF

#define null 0

#define BOARD_SIZE 3

#define PLAYER_NONE 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2

typedef struct _Node {
    int board[BOARD_SIZE][BOARD_SIZE];
} Node;

int minimax(Node* node, int depth, bool maximizingPlayer);

void node_init(Node* node);

bool node_allocate(Node** node);

void node_printBoard(Node* node, char* tokens);

#endif
