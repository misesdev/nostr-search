#ifndef TYPES_C
#define TYPES_C

#define TRIE_CHILDREN_LENGTH 160
#define PUBKEY_ADDRESS_LENGTH 16

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char name[35];
    char pubkey[65]; // 64 bytes + byte null end
    char profile[100];
    struct UserNode *friends;
} User;

struct UserNode {
    User *user;
    struct UserNode *next;
};

struct TrieNode {
    User *user;
    struct TrieNode *children[TRIE_CHILDREN_LENGTH];
    bool isEndOfKey;
};

typedef struct {
    uint8_t address[PUBKEY_ADDRESS_LENGTH];
} UserAddress;

struct FriendNode {
    uint8_t user[PUBKEY_ADDRESS_LENGTH];
    struct FriendNode *next;
};

typedef struct {
    UserAddress user;
    struct FriendNode *friends;
} FriendList;

typedef struct {
    char pubkey[65];
    char search[100];
} Search;

#endif



