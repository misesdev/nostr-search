#ifndef RELAY_LINKED_C
#define RELAY_LINKED_C

#include "../types/types.c"
#include <stdio.h>
#include <stdlib.h>

void insertRelayLinked(LinkedRelays *relays, char *relay)
{
    if(relays->count == relays->size) {
        relays->size += 100;
        relays->relays = realloc(relays->relays, relays->size * sizeof(Relay));
    }

    Relay *relay_info = &relays->relays[relays->count];

    snprintf(relay_info->address, RELAY_SIZE, "%s", relay);

    relays->count++;
}


#endif
