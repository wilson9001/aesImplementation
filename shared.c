#include "shared.h"
#include <stdio.h>

const int Nk[] = {4, 6, 8};
const int Nr[] = {10, 12, 14};
//length of bits in a word, divided into 4 bytes
const int wordLength = 32;
const BYTE MODULO = 0x1b;
const BYTE bitTest[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; //test for which bits in b are set
const BYTE Sbox[16][16] = {
    { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 } ,
    { 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 } ,
    { 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 } ,
    { 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 } ,
    { 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 } ,
    { 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf } ,
    { 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 } ,
    { 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 } ,
    { 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 } ,
    { 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb } ,
    { 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 } ,
    { 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 } ,
    { 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a } ,
    { 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e } ,
    { 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf } ,
    { 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }
    };


void printState(BYTE state[4][Nb])
{
    for(int row = 0; row < 4; row++)
        {
            for(int column = 0; column < Nb; column++)
            {
                printf("%02x", state[row][column]);
            }
        }
}

void printKeySchedule(word w[Nb])
{
    for(int column = 0; column < Nb; column++)
    {
        for(int row = 0; row < 4; row++)
        {
            printf("%02x", w[column][row]);
        }
    }
}

void printIO(BYTE in[4 * Nb])
{
    for(int i = 0; i < 4*Nb; i++)
    {
        printf("%02x", in[i]);
    }
}

void addRoundKey(BYTE state[4][Nb], word w[])
{
    for(int column = 0; column < Nb; column++)
    {
        for(int row = 0; row < 4; row++)
        {
            //printf("\nstate[%d][%d] ^ word[%d][%d] = 0x%02x ^ 0x%02x = 0x%02x", row, column, column, row, state[row][column], w[column][row], state[row][column] ^ w[column][row]);
            state[row][column] ^= w[column][row]; //Inverted indexing because word is typeDef BYTE[4], so we index the word first then the row in the word.
        }
    }
}

BYTE xtime(BYTE in)
{
    BYTE highestBitSet = (in | 0x7f) ^ 0x7f; //determine if highest bit is set. If so it will be lost in the shift and we will need XOR

    in <<= 1;

    if(highestBitSet)
    {
        in ^= MODULO;
    }

    return in;
}

BYTE ffMultiply(BYTE a, BYTE b)
{
    BYTE bitsSet[8];
    BYTE totalSet = 0;

    //printf("\nInside ffMultiply, a = 0x%x, b = 0x%x\nTesting Bits of b:", a, b);

    for (int i = 7; i >= 0; i--)
    {
        if ((bitTest[i] ^ b) < b) //test if a bit was set and now is not
        {
            //printf("\nBit %d was set.", i);
            bitsSet[totalSet] = i;
            totalSet++;
        }
    }

    //printf("\nLargest bit set was %d", bitsSet[0]);

    BYTE xTimeResults[bitsSet[0] + 1];

    xTimeResults[0] = a; //autoset first value since multiplication by 0x01 is the multiplicative identity

    for (int i = 1; i <= bitsSet[0]; i++) //keep feeding xtime to obtain results of multiplying a by higher powers of x
    {
        xTimeResults[i] = xtime(xTimeResults[i - 1]);
       // printf("\nxTime response is: 0x%x", xTimeResults[i]);
    }

    BYTE result = 0x00;

    for (int i = 0; i < totalSet; i++)
    {
        result = result ^ xTimeResults[bitsSet[i]]; //retrieve each result corresponding to a bit set in b and XOR it into the result var to get the result of multiplying by all the x's set in b
        //printf("\nResults currently is 0x%x", result);
    }

    return result;
}

void subBytes(BYTE state[4][Nb],const BYTE SubBox[16][16])
{
    BYTE SRow, SColumn;

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            SRow = state[row][column] >> 4;
            SColumn = (state[row][column] | 0xf0) ^ 0xf0;

            state[row][column] = SubBox[SRow][SColumn];
        }
    }
}

void mixColumns(BYTE state[4][Nb], const BYTE mixingVector[4])
{
    int startingIndex = 0;
    BYTE newByteData[4];
    BYTE newState[4][Nb];

    for (int column = 0; column < Nb; column++)
    {
        //printf("\n--------Column %d--------", column);
        for (int row = 0; row < 4; row++)
        {
            //printf("\n----Row %d----", row);
            for (int i = 0; i < 4; i++)
            {
                newByteData[i] = ffMultiply(mixingVector[(startingIndex + i) % 4], state[i][column]); //create byte to combine later by multiplication with corresponding mix column vector byte
                //printf("\nMultiplying 0x%02x by 0x%02x = 0x%02x", mixingVector[(startingIndex + i) %4], state[i][column], newByteData[i]);
            }
            //printf("\n");
            for (int i = 1; i < 4; i++)
            {
                newByteData[i] = newByteData[i - 1] ^ newByteData[i]; //add each previous entry to current entry. This results in the last entry being the summation of the whole array
                //printf("\nnewByteData[%d] = ox%02x", i, newByteData[i]);
            }

            newState[row][column] = newByteData[3];

            startingIndex--;

            if (startingIndex < 0)
            {
                startingIndex = 3;
            }
        }
    }

    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            state[row][column] = newState[row][column];
        }
    }
}