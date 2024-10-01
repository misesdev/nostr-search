#ifndef USER_BITSET_C
#define USER_BITSET_C

#include "types.c"
#include <stdint.h>
#include <stdlib.h>

#define BITS_PER_BLOCK 64

uint_fast32_t bitsetSize = (MAX_USERS_TO_VISIT + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;

uint_fast64_t* createUserBitset()
{
    return malloc(bitsetSize * sizeof(uint_fast64_t));
}

uint_fast32_t hashPointer(void *pointer)
{
    uintptr_t ptrValue = (uintptr_t) pointer;
    ptrValue = (ptrValue >> 8UL) ^ (ptrValue & 0xFF);
    return (uint_fast32_t)(ptrValue % MAX_USERS_TO_VISIT);
}

void markVisitedUser(uint_fast64_t *bitset, User *user)
{
    uint_fast32_t pointer = hashPointer(user);

    bitset[pointer / BITS_PER_BLOCK] |= 1UL << (pointer % BITS_PER_BLOCK);
}  

bool isVisitedUser(uint_fast64_t *bitset, User *user)
{
    uint_fast32_t pointer = hashPointer(user);

    return (bitset[pointer / BITS_PER_BLOCK] & 1UL << (pointer % BITS_PER_BLOCK)) != 0;
}

void freeUserBitset(uint_fast64_t *bitset)
{
    free(bitset);
}

#endif


