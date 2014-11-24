#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "func.h"

char tokens[] = { ' ', 'X', 'O' };

int main(int argc, char* argv[]) {
    Node node;

    node_init(&node);
    
    node_printBoard(&node, tokens);
}
