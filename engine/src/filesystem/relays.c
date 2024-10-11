#ifndef RELAY_DISK_C
#define RELAY_DISK_C

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../types/types.c"

void loadRelays(Database *database)
{
    long offset = 0;
    uint32_t defaultCount = 0;
    FILE *fileRelays = fopen("./data/relays.db", "rb");

    if(!fileRelays) 
    {
        FILE *file = fopen("./data/relays.db", "wb");
        
        if(!file) return;

        fseek(file, offset, SEEK_SET);
        fwrite(&defaultCount, sizeof(uint32_t), 1, file);
        fclose(file);

        fileRelays = fopen("./data/relays.db", "rb");

        if(!fileRelays) { 
            printf("relays not loaded\n");
            return;
        }
    }

    database->relays = malloc(sizeof(LinkedRelays));

    fseek(fileRelays, offset, SEEK_SET);
    fread(&database->relays->count, sizeof(uint32_t), 1, fileRelays);
    offset += sizeof(uint32_t);

    database->relays->relays = malloc((database->relays->count + 100) * sizeof(Relay));
    database->relays->size = (database->relays->count + 100);

    printf("loading %d relays..\n", database->relays->count);
    for(uint32_t i = 0; i < database->relays->count; i++) 
    {
        fseek(fileRelays, offset, SEEK_SET);
        fread(&(database->relays->relays[i].address), sizeof(char), RELAY_SIZE, fileRelays);
        offset += RELAY_SIZE;
    }

    fclose(fileRelays);
}

void saveRelays(LinkedRelays *relays)
{
    long offset = 0;

    FILE *fileRelays = fopen("./data/relays.db", "wb");

    if(!fileRelays) {
        printf("not found file relays.db");
        return;
    }

    fseek(fileRelays, offset, SEEK_SET);
    fwrite(&relays->count, sizeof(uint32_t), 1, fileRelays);
    offset += sizeof(uint32_t);

    for(uint32_t i = 0; i < relays->count; i++)
    {
        fseek(fileRelays, offset, SEEK_SET);
        fwrite(&(relays->relays[i].address), sizeof(char), RELAY_SIZE, fileRelays);
        offset += RELAY_SIZE;
    }

    fclose(fileRelays);
}


#endif
