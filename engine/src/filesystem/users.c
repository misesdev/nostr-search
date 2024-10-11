#ifndef USERS_DISK_C
#define USERS_DISK_C

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../types/types.c"
#include "../types/user_trie.c"

void loadUser(FILE *file, long *offset, User *user) 
{
    fseek(file, *offset, SEEK_SET);
    fread(user, sizeof(User), 1, file);
    *offset += sizeof(User);
    
    user->friends = NULL;
}

Database* loadUsersFromDisk(FILE *file) 
{
    long offset = 0;
    Database * database = malloc(sizeof(Database));
    database->users = malloc(sizeof(LinkedUsers));
    database->tree = createTrieNode(0);

    fseek(file, offset, SEEK_SET);
    fread(&(database->users->count), sizeof(uint32_t), 1, file);
    offset += sizeof(uint32_t);

    database->users->size = database->users->count + 100;
    database->users->users = malloc(database->users->size * sizeof(User));

    printf("loading %d users..\n", database->users->count);

    for(uint32_t i = 0; i < database->users->count - 1; i++) 
    {
        User *user = &database->users->users[i];

        loadUser(file, &offset, user);
        insertTrieNode(database->tree, user);
    }

    return database;
}

void saveUsers(LinkedUsers *rootUsers)
{
    long offset = 0;
    FILE *fileUsers = fopen("./data/users.db", "wb");

    fseek(fileUsers, offset, SEEK_SET);
    fwrite(&rootUsers->count, sizeof(uint32_t), 1, fileUsers);
    offset += sizeof(uint32_t);

    for(int i = 0; i < rootUsers->count; i++)
    {
        User *user = &rootUsers->users[i];

        fseek(fileUsers, offset, SEEK_SET);
        fwrite(user, sizeof(User), 1, fileUsers);
        offset += sizeof(User);
    }
}

Database* loadUsers()
{
    mkdir("./data", 0777);

    long offset = 0;
    uint32_t defaultUsers = 0;

    FILE *fileUsers = fopen("./data/users.db", "rb");

    if(!fileUsers) 
    {
        FILE *file = fopen("./data/users.db", "wb");
        
        if(!file) return NULL;

        fseek(file, offset, SEEK_SET);
        fwrite(&defaultUsers, sizeof(uint32_t), 1, file);
        fclose(file);

        fileUsers = fopen("./data/users.db", "rb");

        if(!fileUsers) {
            printf("not found file users.db");
            return NULL;
        }
    }
    
    Database* database = loadUsersFromDisk(fileUsers);
   
    fclose(fileUsers);
    
    return database;
}


#endif


