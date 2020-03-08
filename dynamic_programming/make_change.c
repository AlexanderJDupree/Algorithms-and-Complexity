/*
 * File         : make_change.c
 * Description  : Implement a min-change calculator
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree
*/

#include <stdio.h>
#include <string.h>

#define DENOMINATIONS 3
#define INT_MAX ~0U >> 1

typedef enum {
    PENNY  = 1,
    TRIPLE = 3,
    QUIN   = 5
} Coins;

int minimum(int* vals, int n)
{
    int min = vals[0];
    for(int i = 1; i < n; ++i)
    {
        if(vals[i] < min) { min = vals[i]; }
    }
    return min;
}

int __num_coins_recursive(int n)
{
    if(n == 0) { return 0; }
    if(n < 0) { return ~0U >> 1; }

    int vals[DENOMINATIONS] = { __num_coins_recursive(n - PENNY)
                              , __num_coins_recursive(n - TRIPLE)
                              , __num_coins_recursive(n - QUIN)
                              };

    return 1 + minimum(vals, DENOMINATIONS);
}

#if defined(MEMOIZE) || defined(TABULAR)

#ifndef TABLE_MAX
#define TABLE_MAX 1024
#endif // TABLE_MAX

static int TABLE[TABLE_MAX]; 

void init_table()
{
    int* p = TABLE;

    // Find first N solutions up to the highest denomination
    for(int i = 0; i <= QUIN; ++i)
    {
        *(p++) = __num_coins_recursive(i);
    }
    // Fill in -1 for the rest of the table
    for(; p < TABLE + TABLE_MAX; ++p)
    {
        *p = -1;
    }
}

#endif 

#if defined(MEMOIZE)

int num_coins(int n)
{
    if(n == 0) { return 0; }
    if(n < 0) { return ~0U >> 1; }
    if(TABLE[n] == -1)
    {

        int vals[DENOMINATIONS] = { num_coins(n - QUIN)
                                  , num_coins(n - TRIPLE)
                                  , num_coins(n - PENNY)
                                  };

        TABLE[n] =  1 + minimum(vals, DENOMINATIONS);
    }
    return TABLE[n];
}

#elif defined(TABULAR)

int num_coins(int n)
{
    if(n == 0){ return 0; }
    
    // ~0U is unsigned practical infinity, shift right 1 for two's complement
    if(n < 0) { return ~0U >> 1; }

    if(TABLE[n] == -1)
    {
        for (int i = QUIN; i <= n; ++i)
        {

            int vals[DENOMINATIONS] = { TABLE[i - QUIN]
                                      , TABLE[i - TRIPLE]
                                      , TABLE[i - PENNY]
                                      };
            TABLE[i] =  1 + minimum(vals, DENOMINATIONS);
        }
    }
    return TABLE[n];
}

#else

int num_coins(int n)
{
    return __num_coins_recursive(n);
}
#endif

int main(int argc, char** argv)
{
    int verbose = 0;
    if (argc < 2)
    {
        printf("\nmake_change: <value>\n");
        return 1;
    }
    if(argc == 3 && strcmp(argv[2], "-v") == 0)
        verbose = 1;

    int val = atoi(argv[1]);

#if defined(MEMOIZE) || defined(TABULAR)
    if(val >= TABLE_MAX)
    {
        printf("\nError, max value for MEMOIZE or TABULAR algorithm is %d\n", TABLE_MAX - 1);
        return 1;
    }
    init_table();
#endif // MEMOIZE

    int coins= num_coins(val);
    printf("\nNum Coins: %d\n", coins);

#if defined(MEMOIZE) || defined (TABULAR)
    if(verbose)
    {
        printf("\nEnumerated Results:\n[ %d", TABLE[0]);
        for(int i = 1; i <= val; ++i)
        {
            printf(", %d", TABLE[i]);
        }
        printf("]\n");
    }
#endif 

    return 0;
}