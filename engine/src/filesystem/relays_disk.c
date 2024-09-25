#ifndef RELAY_DISK_C
#define RELAY_DISK_C

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../types/types.c"
#include "../types/relay_list.c"

struct RelayNode* loadRelaysFromDisk()
{
    long offset = 0, defaultCount = 0;
    FILE *fileRelays = fopen("./data/relays.db", "rb");

    if(!fileRelays) 
    {
        FILE *file = fopen("./data/relays.db", "wb");
        
        if(!file) return NULL;

        fseek(file, offset, SEEK_SET);
        fwrite(&defaultCount, sizeof(long), 1, file);

        return NULL;
    }

    long relaysCount;
    fseek(fileRelays, offset, SEEK_SET);
    fread(&relaysCount, sizeof(long), 1, fileRelays);
    offset += sizeof(long);

    printf("relays count: %ld\n", relaysCount);

    struct RelayNode *relays;

    for(int i = 0; i < relaysCount; i++) 
    {
        char relayAddress[RELAY_SIZE];
        fseek(fileRelays, offset, SEEK_SET);
        fread(relayAddress, sizeof(char), RELAY_SIZE, fileRelays);
        offset += RELAY_SIZE;

        if(i == 0)
            relays = createRelayNode(relayAddress);

        if(i > 0)
            insertRelayNode(relays, relayAddress);
    }

    return relays;
}


bool loadRelaysOnDisk(struct RelayNode *root)
{
    long offset = 0;

    FILE *fileRelays = fopen("./data/relays.db", "wb");

    if(!fileRelays) return false;

    long relaysCount = countRelayNodes(root);

    fseek(fileRelays, offset, SEEK_SET);
    fwrite(&relaysCount, sizeof(long), 1, fileRelays);
    offset += sizeof(long);

    struct RelayNode *current = root;

    while(current)
    {
        fseek(fileRelays, offset, SEEK_SET);
        fread(current->address, sizeof(char), RELAY_SIZE, fileRelays);
        offset += RELAY_SIZE;

        current = current->next;
    }

    return true;
}


#endif
