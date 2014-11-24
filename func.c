#include "func.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minimax(Node* node, int depth, bool maximizingPlayer) {
    int victor = node_isTerminal(node);

    if (depth == 0 || victor) {
        return node_heuristic(node, victor);
    }
    
    if (maximizingPlayer) {
        int best = -INFINITY;
        
        NodeList* head = node_moves(node, PLAYER_ONE);
        NodeList* next = head;
        while (next != null) { // For each possible move
            int val = minimax(&next->node, depth - 1, false); // recurse for other player's move
            best = best > val ? best : val; // Take the maximum
            next = next->next; // Progress to next possible move
        }

        node_free(head); // Free move list from memory

        return best;
    } else {
        int best = INFINITY;
        
        NodeList* head = node_moves(node, PLAYER_TWO);
        NodeList* next = head;
        while (next != null) { // For each possible move
            int val = minimax(&next->node, depth - 1, true); // recurse for other player's move
            best = best < val ? best : val; // Take the minimum
            next = next->next; // Progress to next possible move
        }

        node_free(head); // Free move list from memory

        return best;
    }
}

// Free a NodeList from memory
void node_free(NodeList* list) {
    NodeList* next = list;
    while (next != null) {
        list = next;
        next = list->next;
        free(list);
    }
}

// Returns a player number if they have won, else 0
int node_isTerminal(Node* node) {
    int ret = 0;

    // check each row
    ret = node->board[0][0] & node->board[1][0] & node->board[2][0];
    if (ret != 0) { return ret; }

    ret = node->board[0][1] & node->board[1][1] & node->board[2][1];
    if (ret != 0) { return ret; }

    ret = node->board[0][2] & node->board[1][2] & node->board[2][2];
    if (ret != 0) { return ret; }

    // check each column
    ret = node->board[0][0] & node->board[0][1] & node->board[0][2];
    if (ret != 0) { return ret; }

    ret = node->board[1][0] & node->board[1][1] & node->board[1][2];
    if (ret != 0) { return ret; }

    ret = node->board[2][0] & node->board[2][1] & node->board[2][2];
    if (ret != 0) { return ret; }

    // check each diagonal
    ret = node->board[0][0] & node->board[1][1] & node->board[2][2];
    if (ret != 0) { return ret; }

    ret = node->board[2][0] & node->board[1][1] & node->board[0][2];
    if (ret != 0) { return ret; }

    return 0;
}

/*
 * x x x = 3
 * x x o = 6
 * x o o = 9
 * o o o = 12
 * ~ ~ ~ = 0
 * x x ~ = 2
 * x ~ ~ = 1
 * o o ~ = 8
 * o ~ ~ = 4
 * x o ~ = 5
 */
void node_rowHeuristic(int a, int b, int c, int* max, int* min) {
    int swiddle = a + b + c;

    switch (swiddle) {
        case 3:
            *max = INFINITY;
            //*min = 1;
            break;
        case 12:
            //*max = 1;
            *min = INFINITY;
            break;
        case 6:
        case 9:
        case 0:
        case 5:
            //*max = 1;
            //*min = 1;
            break;
        case 2:
            *max *= 100;
            //*min = 1;
            break;
        case 1:
            *max *= 10;
            //*min = 1;
            break;
        case 8:
            //*max = 1;
            *min *= 100;
            break;
        case 4:
            //*max = 1;
            *min *= 10;
            break;
    }
}

int node_heuristic(Node* node, int victor) {
    if (victor == 0) {
        int max = 1;
        int min = 1;

        // check each row
        node_rowHeuristic(node->board[0][0], node->board[1][0], node->board[2][0], &max, &min);
        node_rowHeuristic(node->board[0][1], node->board[1][1], node->board[2][1], &max, &min);
        node_rowHeuristic(node->board[0][2], node->board[1][2], node->board[2][2], &max, &min);

        // check each column
        node_rowHeuristic(node->board[0][0], node->board[0][1], node->board[0][2], &max, &min);
        node_rowHeuristic(node->board[1][0], node->board[1][1], node->board[1][2], &max, &min);
        node_rowHeuristic(node->board[2][0], node->board[2][1], node->board[2][2], &max, &min);

        // check each diagonal
        node_rowHeuristic(node->board[0][0], node->board[1][1], node->board[2][2], &max, &min);
        node_rowHeuristic(node->board[2][0], node->board[1][1], node->board[0][2], &max, &min);

        return max - min;
    } else if (victor == MAXIMIZING_PLAYER) {
        return INFINITY;
    } else {
        return -INFINITY;
    }
}

void node_init(Node* node) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            node->board[x][y] = PLAYER_NONE;
        }
    }
}

bool node_allocate(Node** node) {
    *node = malloc(sizeof(Node));
    
    if (*node == null) {
        return false;
    } else {
        node_init(*node);
        return true;
    }
}

bool list_allocate(NodeList** list) {
    *list = malloc(sizeof(NodeList));
    
    if (*list == null) {
        return false;
    } else {
        (*list)->next = null;
        return true;
    }
}

void node_clone(Node* src, Node* dst) {
    memcpy(dst, src, sizeof(Node));
    //for (int x = 0; x < BOARD_SIZE; x++) {
    //    for (int y = 0; y < BOARD_SIZE; y++) {
    //        dst->board[x][y] = src->board[x][y];
    //    }
    //}
}

NodeList* node_moves(Node* node, int player) {
    NodeList* head = null;
    NodeList* tail = null;

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            NodeList* next = null;

            if (node->board[x][y] == PLAYER_NONE && list_allocate(&next)) {
                if (head == null) {
                    head = tail = next;
                } else {
                    tail->next = next;
                    tail = next;
                }

                node_clone(node, &tail->node);
                tail->node.board[x][y] = player;
            }
        }
    }

    return head;
}

// X |   | O 
//---|---|---
// O | X | X
//---|---|---
//   | O | O
void node_printBoard(Node* node, char* tokens) {
    system("clear");

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            printf(" %c ", tokens[node->board[x][y]]);
            
            if (x < BOARD_SIZE - 1) {
                printf("|");
            }
        }

        printf("\n");

        if (y < BOARD_SIZE - 1) {
            for (int x = 0; x < BOARD_SIZE * 4 - 1; x++) {
                printf("-");
            }

            printf("\n");
        }
    }
}
