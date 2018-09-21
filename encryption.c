#include "encryption.h"

void cipher(BYTE* in/*[4 * Nb]*/, BYTE* out/*[4 * Nb]*/, word* w, keyLength currentKeyLength)
{
    BYTE state[4][Nb];

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            state[row][column] = in[row + (4 * column)];
        }
    }

    addRoundKey(state, w[0]/*[Nb - 1]*/); //Only going to pass in pointer to first word, will iterate from pointer in actual function

    for (int round = 1; 1 < Nr[currentKeyLength]; round++)
    {
        subBytes(state, Sbox);
        shiftRows(state);
        mixColumns(state, mixColumnVector);
        addRoundKey(state, w[round * Nb]);
    }

    subBytes(state, Sbox);
    shiftRows(state);
    addRoundKey(state, w[Nr[currentKeyLength] * Nb]);

    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            out[row + (4 * column)] = state[row][column];
        }
    }
}

void shiftRows(BYTE** state/*[4][Nb]*/)
{
    BYTE rowCopy[Nb];

    for (int row = 1; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            rowCopy[column] = state[row][column];
        }

        for (int column = 0; column < Nb; column++)
        {
            state[row][column] = rowCopy[(row + column) % Nb];
        }
    }
}