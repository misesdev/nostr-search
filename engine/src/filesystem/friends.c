#ifndef FRIENDS_DISK_C
#define FRIENDS_DISK_C

#include <stdint.h>
#include <stdio.h>

#include "../types/types.c"
#include "../types/user_list.c"
#include "../utils/user_utils.c"

void loadFriendsFromUser(FILE *file, LinkedUsers *rootUsers, User *user, long *offset)
{
    uint32_t count = 0;
    fseek(file, *offset, SEEK_SET);
    fread(&count, sizeof(uint32_t), 1, file);
    *offset += sizeof(uint32_t);

    uint32_t friends[count];
    fseek(file, *offset, SEEK_SET);
    fread(&friends, sizeof(uint32_t), count, file);
    *offset += (count * sizeof(uint32_t));

    for(int i = 0; i < count; i++)
    {
        User *friend = &rootUsers->users[friends[i]];

        if(i == 0) user->friends = createUserNode(friend);
        
        else insertUserNode(user->friends, friend);
    }
}

void loadFriends(LinkedUsers *rootUsers)
{
    long offset = 0;
    uint32_t currentUser = 0, usersCount = 0;
    FILE *fileFriends = fopen("./data/friends.db", "rb");

    if(!fileFriends) 
    {
        FILE *file = fopen("./data/friends.db", "wb");
        
        if(!file) return;;

        fseek(file, offset, SEEK_SET);
        fwrite(&usersCount, sizeof(uint32_t), 1, file);
        fclose(file);

        fileFriends = fopen("./data/users.db", "rb");

        if(!fileFriends) return;
    }

    fseek(fileFriends, offset, SEEK_SET);
    fread(&usersCount, sizeof(uint32_t), 1, fileFriends);
    offset += sizeof(uint32_t);

    printf("loading %d friends..\n", usersCount);
    for(int i = 0; i < usersCount; i++)
    {
        User *user = &rootUsers->users[i];

        loadFriendsFromUser(fileFriends, rootUsers, user, &offset);
    }

    fclose(fileFriends);
}

void saveFriendsOfUser(FILE *file, LinkedUsers *rootUsers, User *user, long *offset)
{
    if(!user->friends) return;

    uint32_t count = getFriendsCount(user);

    fseek(file, *offset, SEEK_SET);
    fwrite(&count, sizeof(uint32_t), 1, file);
    *offset += sizeof(uint32_t);

    uint32_t friends[count], i = 0;
    struct UserNode *current = user->friends;
    while(current)
    {
        friends[i] = current->user->index;
        current = current->next;
        i++;
    }

    fseek(file, *offset, SEEK_SET);
    fwrite(&friends, sizeof(uint32_t), count, file);
    *offset += (count * sizeof(uint32_t));
}

void saveFriends(LinkedUsers *rootUsers)
{
    long offset = 0;
    FILE *fileFriends = fopen("./data/friends.db", "wb");

    fseek(fileFriends, offset, SEEK_SET);
    fwrite(&(rootUsers->count), sizeof(uint32_t), 1, fileFriends);
    offset += sizeof(uint32_t);

    for(uint32_t i = 0; i < rootUsers->count; i++)
    {
        User *user = &rootUsers->users[i];

        saveFriendsOfUser(fileFriends, rootUsers, user, &offset); 
    }

    fclose(fileFriends);
}


#endif


