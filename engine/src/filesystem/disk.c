#ifndef WDISK_C
#define WDISK_C

#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./users.c"
#include "./friends.c"
#include "./relays.c"
#include "../types/types.c"

void saveDatabase(Database *root, int scope) 
{
    if(scope == SCOPE_USERS || scope == SCOPE_ALL) {
        printf("saving users..\n");
        saveUsers(root->users);
    }

    if(scope == SCOPE_FRIENDS || scope == SCOPE_ALL) {
        printf("saving friends..\n");   
        saveFriends(root->users);
    }

    if(scope == SCOPE_RELAYS || scope == SCOPE_ALL) {
        printf("saving relays..\n");
        saveRelays(root->relays);
    }
}

Database* loadDatabase()
{
    Database* database = loadUsers();

    loadFriends(database->users);
    
    loadRelays(database);

    return database;
}

#endif


