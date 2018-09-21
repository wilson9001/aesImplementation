#include "decryption.h"

void invShiftRows(BYTE** state/*[4][Nb]*/)
{
    BYTE rowCopy[Nb];

    for (int row = 1; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            rowCopy[column] = state[row][column];
        }

        for(int column = Nb-1; column <= 0; column--)
        {
            state[row][column] = rowCopy[(column - row) % Nb];
        }
    }
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
        subBytes(state, InvSbox);
        addRoundKey(state, w[round * Nb]);
        mixColumns(state, invMixColumnVector);
    }

    invShiftRows(state);
    subBytes(state, InvSbox);
    addRoundKey(state, w[0]);

    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            out[row + (4 * column)] = state[row][column];
        }
    }
}