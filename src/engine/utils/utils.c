#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>

int mod(int number) 
{
    return number % 2;
}

int getRowInteger(char character)
{
    if(isalpha(character))
    {
        return toupper(character) - 'A' + 10;
    }
    return character - '0';
}

uint8_t* hexToBytes(char *hex) 
{
    int length = strlen(hex);
    uint8_t *bytes = malloc((length / 2) * sizeof(uint8_t));

    int index = 0;
    uint8_t decimal;
    for(uint8_t i = 0; i < length; i += 2)
    {
        decimal = getRowInteger(hex[i]) * 16;
        decimal += getRowInteger(hex[i + 1]);
        bytes[index] = decimal;
        index++;
    }

    return bytes;
}

char* bytesToHex(uint8_t *bytes) 
{

    return NULL;
}

char* hexToCharacters(char *hex)
{
    return NULL;
}


