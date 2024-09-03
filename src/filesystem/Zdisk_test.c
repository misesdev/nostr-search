#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../types/user_trie.c"
#include "../filesystem/wdisk.c"
#include "../filesystem/rdisk.c"
#include "../utils/utils.c"

User* createUser(char *name, char *pubkey)
{
    User *user = malloc(sizeof(User));
    strcpy(user->name, "Mises Dev");
    strcpy(user->pubkey, pubkey);
    strcpy(user->profile, "");
    return user;
}

int main() 
{
    char pubkey[3][65] = {
        "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93",
        "3da979448d9ba263864c4d6f14984c423a3838364ec255f03c7904b1ae77f206",
        "bf2376e17ba4ec269d10fcc996a4746b451152be9031fa48e74553dde5526bce"
    };
    
    struct TrieNode *root = createTrieNode(); 

    insertTrieNode(root, createUser("Mises Dev", pubkey[0]), NULL);
    insertTrieNode(root, createUser("Alexandre de Morais", pubkey[1]), NULL);
    insertTrieNode(root, createUser("Adouf Hitler", pubkey[2]), NULL);
    
    if(!loadTrieInDisk(root)) return -1;

    struct TrieNode *t_root = loadTrieFromDisk();

    if(!t_root) {
        printf("Error when trying to load the disk tree");
        return -1;
    }

    uint8_t address[16];
    compressPubkey(pubkey[0], address);

    struct TrieNode *t_node = getTrieNode(t_root, address);

    if(t_node) {
        printf("Found user: %s", t_node->user->name);
    }
    
    return 0;
}
