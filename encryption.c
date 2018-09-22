#include "encryption.h"
#include <stdio.h>

const BYTE mixColumnVector[] = {0x02, 0x03, 0x01, 0x01};

void cipher(BYTE in[4 * Nb], BYTE out[4 * Nb], word w[], keyLength currentKeyLength)
{
    BYTE state[4][Nb];
    //printf("\nBegin copying to state\n");
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            //printf("\nState[%d][%d] = 0x%02x", row, column, in[row+(4*column)]);
            state[row][column] = in[row + (4 * column)];
        }
    }
    //printf("\nAdd first round key");
    addRoundKey(state, &w[0]/*[Nb - 1]*/); //Only going to pass in pointer to first word, will iterate from pointer in actual function
    //printf("\nBegin encryption rounds");
    for (int round = 1; round < Nr[currentKeyLength]; round++)
    {
        subBytes(state, Sbox);
        shiftRows(state);
        mixColumns(state, mixColumnVector);
        addRoundKey(state, &w[round * Nb]);
    }
    //printf("\nFinal encryption round");
    subBytes(state, Sbox);
    shiftRows(state);
    addRoundKey(state, &w[Nr[currentKeyLength] * Nb]);

    //printf("\nCopying state to out");
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < Nb; column++)
        {
            //printf("\nout[%d] = state[%d][%d] = 0x%02x", row+(4*column), row, column, state[row][column]);
            out[row + (4 * column)] = state[row][column];
        }
    }
    //printf("\nEncryption complete");
}

void shiftRows(BYTE state[4][Nb])
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