#include <stdio.h>
#include "./trie.c"
#include "./utils.c"

int main(int argc, char *args[]) 
{
    int* numbers = toArray("FF22");

    printf("first: %d, second: %d", numbers[0], numbers[1]);
}
