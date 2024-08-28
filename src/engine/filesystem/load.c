#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"

struct TrieNode* loadData() 
{
    FILE *file = fopen("database", "wb");
    
    if(!file) return NULL;

    for(int i = 0;i < 32; i++) {    }

    return NULL;
}

