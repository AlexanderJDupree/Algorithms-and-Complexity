/*
 * File         : choose.c
 * Description  : Binomial Coefficent calculator
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(MEMOIZE) || defined(TABULAR)
// Main must initialize this table before calling choose
unsigned long** TABLE = NULL;

unsigned long** init_table(unsigned n, unsigned m, unsigned initializer)
{
    unsigned long** table = malloc(n * sizeof(unsigned long*));
    for(unsigned i = 0; i < n; ++i)
    {
        table[i] = malloc(m * sizeof(unsigned long));
    }

    for(unsigned i = 0; i < n; ++i)
    {
        for(unsigned j = 0; j < m; ++j)
        {
            table[i][j] = initializer;
        }
    }
    return table;
}

void free_table(unsigned long** table, unsigned n)
{
    for(unsigned i = 0; i < n; ++i)
    {
        free(table[i]);
    }
    free(table);
}

#endif 

#if defined(MEMOIZE)

unsigned long choose(unsigned n, unsigned k)
{
    if(k > n)                { return 0; }
    if(n == k || k == 0)     { return 1; }
    if(k == 1 || k == (n-1)) { return n; }

    if(TABLE[n][k] == 0)
    {
        TABLE[n][k] = choose(n - 1, k - 1) + choose(n - 1, k);
        // Pascal's triangle is symmetric
        TABLE[n][n-k] = TABLE[n][k];
    }
    return TABLE[n][k];
}

#elif defined(TABULAR)

unsigned min(unsigned a, unsigned b)
{
    return (a < b) ? a : b;
}

unsigned long choose(int n, int k)
{
    if(k > n) { return 0; }

    TABLE[0][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j <= min(i, k); ++j)
        {
            unsigned long left  = (j - 1 < 0) ? 0 : TABLE[i-1][j-1];
            unsigned long right = (j > i - 1) ? 0 : TABLE[i-1][j];

            TABLE[i][j] = left + right;
        }
    }
    return TABLE[n][k];
}

#else

unsigned long choose(unsigned n, unsigned k)
{
    if(k > n)                { return 0; }
    if(n == k || k == 0)     { return 1; }
    if(k == 1 || k == (n-1)) { return n; }

    return choose(n - 1, k - 1) + choose(n - 1, k);
}

#endif 

int help()
{
    fprintf(stderr, "\nusage: choose <n> <k>\n\tBinomial Coefficient calculator\n");
    return 1;
}

unsigned convert_to_uint(char* arg)
{
    char* endptr = arg;
    long long val = strtoll(arg, &endptr, 0);
    if(*endptr != '\0' || val < 0  || val > UINT32_MAX)
    {
        fprintf(stderr, "\nchoose: Fatal, bad input");
        exit(help());
    }
    return val;
}

int main(int argc, char** argv)
{
    if(argc != 3)
        return help();

    unsigned n = convert_to_uint(argv[1]);
    unsigned k = convert_to_uint(argv[2]);

#if defined(MEMOIZE) || defined(TABULAR)

    TABLE = init_table(n + 1, k + 1, 0);

    unsigned long result = choose(n, k);
#else
    unsigned long result = choose(n, k);
#endif 

    printf("\n%u `choose` %u = %lu\n", n, k, result);

#if defined(MEMOIZE) || defined(TABULAR)
    free_table(TABLE, n + 1);
#endif 
    exit(0);
}