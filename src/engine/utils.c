#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getRowInteger(char character)
{
    if(isalpha(character))
    {
        return toupper(character) - 'A' + 10;
    }
    return character - '0';
}

int hexToInteger(char* hexByte)
{
    int power = 1;
    int decimal = 0;
    int length = strlen(hexByte) -1;
    
    for (int i = length; i >= 0; i--) 
    {
        decimal += getRowInteger(hexByte[i]) * power;
        power *= 16;
    }

    return decimal;
}

int* hexToBytes(char *npub, int array[]) 
{
    int length = strlen(npub); 

    if(length % 2 != 0) 
    {
        printf("Invalid hexadecimal bytes");
        return NULL;
    }
    
    int index = 0;
    char hexByte[2];
    for(int i = 0; i <= length - 2; i += 2)
    {
        hexByte[0] = npub[i];
        hexByte[1] = npub[i + 1];

        array[index] = hexToInteger(hexByte);

        index++;
    }

    return array;
}



