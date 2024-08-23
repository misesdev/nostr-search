#include <stdint.h>
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

#include "./trie.c"
#include "./utils/utils.c"
#include "./filesystem/load.c"

int main(int argc, char *args[]) 
{
    char npub[] = "ff22";

    uint8_t *numbers = hexToBytes(npub);

    printf("first: %d, second: %d", numbers[0], numbers[1]);

    //User *user = loadData();

    //if(!user) {
        //printf("File 'database.bin' not found!");
    //}

    //printf("The user is: %s", user->name);

    free(numbers);
    //free(user);
}


