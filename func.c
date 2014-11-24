#include "func.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minimax(Node* node, int depth, bool maximizingPlayer) {
    
    return 0;
}

void node_init(Node* node) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            (*node)->board[x][y] = PLAYER_NONE;
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

// X |   | O 
//---|---|---
// O | X | X
//---|---|---
//   | O | O
void node_printBoard(Node* node, char* tokens) {
    system("clear")

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
