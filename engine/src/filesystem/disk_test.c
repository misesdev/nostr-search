#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../types/user_trie.c"
#include "../filesystem/wdisk.c"
#include "../filesystem/rdisk.c"

User* createUser(char *name, char *pubkey)
{
    User *user = malloc(sizeof(User));
    strcpy(user->name, name);
    strcpy(user->pubkey, pubkey);
    strcpy(user->profile, "");
    user->friends = createUserNode(NULL);
    return user;
}

void showUsersOfTrie(struct TrieNode *root)
{
    struct TrieList *list = root->childrens;

    while(list) {
        showUsersOfTrie(list->node);
    }

    if(root->isEndOfKey) {
        printf("username: %s\n", root->user->name);
        struct UserNode *friends = root->user->friends;
        while(friends) {
            printf("    friend: %s\n", friends->user->name);
            friends = friends->next;
        }
    }
}

int main() 
{
    char pubkey[3][65] = {
        "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93",
        "3da979448d9ba263864c4d6f14984c423a3838364ec255f03c7904b1ae77f206",
        "bf2376e17ba4ec269d10fcc996a4746b451152be9031fa48e74553dde5526bce"
    };
    
    struct TrieNode *root = createTrieNode(0); 

    struct TrieNode *mises = insertTrieNode(root, createUser("Mises Dev", pubkey[0]));
    struct TrieNode *alex = insertTrieNode(root, createUser("Alexandre de Morais", pubkey[1]));
    struct TrieNode *hitler = insertTrieNode(root, createUser("Adouf Hitler", pubkey[2]));

    // // Mises Dev friends
    // insertUserNode(mises->user->friends, alex->user);
    // insertUserNode(mises->user->friends, hitler->user);

    // // Alexandre de Morais friends
    // insertUserNode(alex->user->friends, hitler->user);

    // // Hitler friends
    // insertUserNode(hitler->user->friends, alex->user);
    
    // if(!loadTrieInDisk(root)) return -1;

    // destroyTrieNode(root);

    // struct TrieNode *t_root = loadTrieFromDisk();

    // if(!t_root) {
    //     printf("Error when trying to load the disk tree");
    //     return -1;
    // }

    // showUsersOfTrie(t_root);
    
    return 0;
}
