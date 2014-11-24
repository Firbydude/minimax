#ifndef FUNC_H
#define FUNC_H

#include <stdbool.h>

#define INFINITY 0x7FFFFFFF

#define null 0

#define BOARD_SIZE 3

#define PLAYER_NONE 0
#define PLAYER_ONE 1
#define PLAYER_TWO 4
#define MAXIMIZING_PLAYER PLAYER_ONE

typedef struct _Node {
    int board[BOARD_SIZE][BOARD_SIZE];
} Node;

struct _NodeList;
typedef struct _NodeList {
    Node node;
    struct _NodeList* next;
} NodeList;

int minimax(Node* node, int depth, bool maximizingPlayer);

void node_init(Node* node);

bool node_allocate(Node** node);

void node_printBoard(Node* node, char* tokens);

NodeList* node_moves(Node* node, int player);

void node_free(NodeList* list);

int node_isTerminal(Node* node);

void node_rowHeuristic(int a, int b, int c, int* max, int* min);

int node_heuristic(Node* node, int victor);

bool list_allocate(NodeList** list);

void node_clone(Node* src, Node* dst);

#endif
