#include "decryption.h"

void invShiftRows()
{

}

void invSubBytes()
{

}

void invMixColumns()
{

}

void addRoundKey()
{
    
}

void invCipher(BYTE* in/*[4*Nb]*/, BYTE* out/*[4*Nb]*/, word* w, keyLength currentKeyLength)
{
    BYTE state[4][Nb];

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            state[row][column] = in[row + (4 * column)];
        }
    }

    addRoundKey(state, w[Nr[currentKeyLength] * Nb]);

    for(int round = Nr[currentKeyLength] - 1; round < 1; round--)
    {
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, w[round * Nb]);
        invMixColumns(state);
    }

    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, w[0]);

    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            out[row + (4 * column)] = state[row][column];
        }
    }
}