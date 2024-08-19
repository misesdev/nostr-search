#include <stdio.h>
#include <string.h>
#include "./trie.c"
#include "./utils.c"

int main(int argc, char *args[]) 
{
    char npub[] = "ff22";
    int numbers[strlen(npub) / 2];

    hexToBytes("FF22", numbers);

    printf("first: %d, second: %d", numbers[0], numbers[1]);
}
