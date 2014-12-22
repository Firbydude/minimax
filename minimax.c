#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "func.h"

char tokens[] = { ' ', 'X', 'O' };

int main(int argc, char* argv[]) {
    Node node;
    int moveX;
    int moveY;
    int victor;

    node_init(&node);
    
    do {
        node_printBoard(&node);
        printf("Make a move\n");
        scanf("%i %i", &moveX, &moveY);

        victor = node_isTerminal(&node);
        if (victor == PLAYER_ONE) {
            printf("Player 1 wins!");
            return 0;
        } else if (victor == DRAW) {
            printf("Draw");
            return 0;
        }

        node.board[moveX][moveY] = PLAYER_ONE;
        minimax(&node, 8, false, &node);
        
        victor = node_isTerminal(&node);
        if (victor == PLAYER_TWO) {
            printf("Player 2 wins!");
            return 0;
        } else if (victor == DRAW) {
            printf("Draw");
            return 0;
        }
    } while (true);

    return 0;
}
