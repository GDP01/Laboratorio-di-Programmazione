#include "misura.h"

misura::misura(lettura let0, lettura let1, lettura let2, lettura let3, lettura let4, lettura let5, lettura let6, lettura let7, lettura let8, lettura let9, lettura let10, lettura let11, lettura let12, lettura let13, lettura let14, lettura let15, lettura let16)
    {
        mis[0] = let0;
        mis[1] = let1;
        mis[2] = let2;
        mis[3] = let3;
        mis[4] = let4;
        mis[5] = let5;
        mis[6] = let6;
        mis[7] = let7;
        mis[8] = let8;
        mis[9] = let9;
        mis[10] = let10;
        mis[11] = let11;
        mis[12] = let12;
        mis[13] = let13;
        mis[14] = let14;
        mis[15] = let15;
        mis[16] = let16;
    }

misura::misura()
{
    mis[0] = lettura();
    mis[1] = lettura();
    mis[2] = lettura();
    mis[3] = lettura();
    mis[4] = lettura();
    mis[5] = lettura();
    mis[6] = lettura();
    mis[7] = lettura();
    mis[8] = lettura();
    mis[9] = lettura();
    mis[10] = lettura();
    mis[11] = lettura();
    mis[12] = lettura();
    mis[13] = lettura();
    mis[14] = lettura();
    mis[15] = lettura();
    mis[16] = lettura();
}