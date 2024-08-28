#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "./trie.c"
#include "./utils/utils.c"
//#include "./filesystem/load.c"
//#include "./types/linked_lists.c"
#include "./utils/http_utils.c"
#include "./types/user_trie.c"

int main(int argc, char *args[]) 
{
    uint8_t *address = hexToBytes("6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93");

    for(uint8_t i = 0; i < 32; i++) {
         printf("%d ", address[i]);
    }

    free(address);
}


