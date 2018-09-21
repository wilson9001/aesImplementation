#include "shared.h"

void addRoundKey(BYTE** state/*[4][Nb]*/, word* w/*[Nb]*/)
{
    for(int column = 0; column < Nb; column++)
    {
        for(int row = 0; row < 4; row++)
        {
            state[row][column] ^= w[column][row]; //Inverted indexing because word is typeDef BYTE[4], so we index the word first then the row in the word.
        }
    }
}

BYTE xtime(BYTE in)
{
    const MODULO = 0x1b;

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
    const BYTE bitTest[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}; //test for which bits in b are set

    BYTE bitsSet[8];
    BYTE totalSet = 0;

    for (int i = 7; i >= 0; i--)
    {
        if ((bitTest[i] ^ b) < b) //test if a bit was set and now is not
        {
            bitsSet[totalSet] = i;
            totalSet++;
        }
    }

    BYTE xTimeResults[bitsSet[0] + 1];

    xTimeResults[0] = a; //autoset first value since multiplication by 0x01 is the multiplicative identity

    for (int i = 0; i <= bitsSet[0]; i++) //keep feeding xtime to obtain results of multiplying a by higher powers of x
    {
        xTimeResults[i] = xtime(xTimeResults[i - 1]);
    }

    BYTE result = 0x00;

    for (int i = 0; i < totalSet; i++)
    {
        result = result ^ xTimeResults[bitsSet[i]]; //retrieve each result corresponding to a bit set in b and XOR it into the result var to get the result of multiplying by all the x's set in b
    }

    return result;
}

void subBytes(BYTE** state/*[4][Nb]*/, BYTE** SubBox/*[16][16]*/)
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

void mixColumns(BYTE** state/*[4][Nb]*/, BYTE* mixingVector/*[4]*/)
{
    int startingIndex = 0;
    BYTE newByteData[4];

    for (int column = 0; column < Nb; column++)
    {
        BYTE currentColumn[] = {state[0][column], state[1][column], state[2][column], state[3][column]};

        for (int row = 0; row < 4; row++)
        {
            for (int i = 0; i < 4; i++)
            {
                newByteData[i] = ffMultiply(mixingVector[(startingIndex + i) % 4], state[i][column]); //create byte to combine later by multiplication with corresponding mix column vector byte
            }

            for (int i = 1; i < 4; i++)
            {
                newByteData[i] = newByteData[i - 1] ^ newByteData[i]; //add each previous entry to current entry. This results in the last entry being the summation of the whole array
            }

            state[row][column] = newByteData[3];

            startingIndex--;

            if (startingIndex < 0)
            {
                startingIndex = 3;
            }
        }
    }
}