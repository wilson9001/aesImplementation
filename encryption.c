#include "encryption.h"

void cipher(BYTE in[4*Nb], BYTE out[4*Nb], word* w, keyLength currentKeyLength) 
{
    BYTE state[4][Nb];

    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            state[row][column] = in[row + (4*column)];
        }
    }

    addRoundKey(state, w[0][Nb-1]);

    for(int round = 1; 1 < Nr[currentKeyLength]; round++)
    {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, w[round*Nb][(round +1)*(Nb -1)]);
    }

    subBytes(state);
    shiftRows(state);
    addRoundKey(state, w[Nr[currentKeyLength]*Nb][(Nr[currentKeyLength] +1)*(Nb -1)]);
    
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            out[row + (4*column)] = state[row][column];
        }
    }
}

void subBytes(BYTE state[4][Nb])
{
    BYTE SRow, SColumn;

    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < Nb; column++)
        {
            SRow = state[row][column] >> 4;
            SColumn = (state[row][column] | 0xf0) ^ 0xf0;

            state[row][column] = Sbox[SRow][SColumn];
        }
    }
}

void shiftRows(BYTE state[4][Nb])
{

}

void mixColumns(BYTE state[4][Nb])
{

}

void addRoundKey(BYTE state[4][Nb], word* w)
{

}