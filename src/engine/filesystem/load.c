#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"

User* loadData() 
{
    FILE *file = fopen("database.bin", "wb");
    
    if(!file) {
        return NULL;
    }

    User *user = malloc(sizeof(User));


    strcpy(user->name, "Mises Dev");

    for(int i = 0;i < 32; i++) {
        user->npub[i] = 255;
    }

    return user;
}

