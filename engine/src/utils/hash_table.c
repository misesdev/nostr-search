#ifndef HASH_TABLE_C
#define HASH_TABLE_C

#include <stdlib.h>
#include <stdint.h>

#include "./utils.c"

#define MAX_KEYS 50000

uint8_t* createHashMap()
{
    uint8_t *hashMap = calloc(MAX_KEYS, sizeof(uint8_t));

    return hashMap;
}

int createHashKey(char *pubkey)
{
    int hash = 0;
    uint8_t address[16];
    compressPubkey(pubkey, address);

    for(int i = 0; i < 16; i++)
        hash = (hash * 31 + address[i]) % MAX_KEYS;
    
    return hash;
}

void insertHashMap(uint8_t *hashMap, char *pubkey)
{
    int hashKey = createHashKey(pubkey);

    hashMap[hashKey] = 1;
}

bool hashMapContainsKey(uint8_t *hashMap, char *pubkey)
{
    int hashKey = createHashKey(pubkey);

    if(hashMap[hashKey] == 0) {
        hashMap[hashKey] = 1;
        return false;
    }

    return true;
}


#endif

