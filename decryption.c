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

void invCipher(BYTE in[4*Nb], BYTE out[4*Nb], word *w, keyLength currentKeyLength)
{
    BYTE* state;

    state = in;

    addRoundKey(state, w[Nr[currentKeyLength]*Nb][(Nr[currentKeyLength]+1)*(Nb -1)]);

}