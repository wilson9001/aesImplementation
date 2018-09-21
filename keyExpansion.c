#include "keyExpansion.h"

void subWord(word w)
{
    BYTE SRow, SColumn;

    for(int row = 0; row < 4; row++)
    {
        SRow = w[row] >> 4;
        SColumn = (w[row] | 0xf0) ^ 0xf0;

        w[row] = Sbox[SRow][SColumn];
    }
}

void rotWord(word w)
{
    word oldWord;

    for(int row = 0; row < 4; row++)
    {
        oldWord[row] = w[row];
    }

    for(int row = 0; row < 4; row++)
    {
        w[row] = oldWord[(row + 1) % 4];
    }
}

void keyExpansion(BYTE key[], word w[], keyLength currentKeyLength)
{
    word temp;

    int column;

    for (column = 0; column < Nk[currentKeyLength]; column++)
    {
        for(int row = 0; row < 4; row++)
        {
            w[column][row] = key[(4*column) + row];
        }
    }

    for (column = Nk[currentKeyLength]; column < Nb * (Nr[currentKeyLength] + 1); column++)
    {
        for(int row = 0; row < 4; row++)
        {
            temp[row] = w[column - 1][row];
        }

        if((column % Nk[currentKeyLength]) == 0)
        {
            //change temp in rotWord
            rotWord(temp);
            //change temp in subword
            subWord(temp);
            //then XOR with Rcon
            for(int row = 0; row < 4; row++)
            {
                temp[row] ^= Rcon[(column/Nk[currentKeyLength]) + row];
            }
        }
        else if ((Nk[currentKeyLength] > Nk[KL192]) && (column % Nk[currentKeyLength] == 4))
        {
            subWord(temp);
        }

        for(int row = 0; row < 4; row++)
        {
            w[column][row] = (w[column - Nk[currentKeyLength]][row] ^ temp[row]);
        }
    }
}