/*
 * File         : rod_cutting.c
 * Description  : Algorithms for the rod-cutting problem. 
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Greedy Algorithm, doesn't return max profit.
   Fails on rod of length four with prices points
   [0, 2, 5, 9, 9];
   Returns 10, should return 11
int rod_cutting(int* prices, unsigned length)
{
    if(length <= 0) { return 0; }

    int max  = 0;
    int unit = 1;
    for(int i = 1; i <= length; ++i)
    {
        int sale_price = (length / i) * prices[i];

        if(sale_price > max) 
        { 
            max = sale_price; 
            unit = i;
        }
    }
    return max + rod_cutting(prices, length % unit);
}
*/

unsigned max(unsigned a, unsigned b)
{
    return (a > b) ? a : b;
}

#if defined(MEMOIZE) || defined(TABULAR)

static int* TABLE = NULL;

void init_table(unsigned length)
{
    TABLE = (int*) malloc(sizeof(int) * length + 1);
    for(int i = 1; i < length + 1; ++i)
    {
        TABLE[i] = -1;
    }
    TABLE[0] = 0;
}
#endif 

#if defined(MEMOIZE)
unsigned rod_cutting(unsigned* prices, unsigned length)
{
    if(length <= 0)
        return 0;

    if(TABLE[length] == -1)
    {
        unsigned max_price = 0;
        for(int i = 0; i < length; ++i)
        {
            max_price = max(max_price, prices[i] + rod_cutting(prices, length - i - 1));
        }
        TABLE[length] = max_price;
    }
    return TABLE[length];
}

#elif defined(TABULAR)

unsigned rod_cutting(unsigned* prices, unsigned length)
{
    int table[length + 1];
    table[0] = 0;

    for(int i = 0; i <= length; ++i)
    {
        int max_price = 0;
        for(int j = 0; j < i; ++j)
        {
            max_price = max(max_price, prices[j] + table[i - j - 1]);
        }
        table[i] = max_price;
    }
    return table[length];
}

#else
unsigned rod_cutting(unsigned* prices, unsigned length)
{
    if(length <= 0)
        return 0;

    unsigned max_price = 0;
    for(int i = 0; i < length; ++i)
    {
        max_price = max(max_price, prices[i] + rod_cutting(prices, length - i - 1));
    }
    return max_price;
}
#endif 

int help()
{
    fprintf(stderr, "\nusage: rod_cutting <num> \n");
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

void get_prices(unsigned* prices, unsigned n)
{
    char buffer[1024];

    for (size_t i = 0; i < n; ++i)
    {
        printf("\nEnter Price for unit of length %lu: ", i + 1);
        scanf("%s", buffer);
        prices[i] = convert_to_uint(buffer);
    }
}

int main(int argc, char** argv)
{
    if(argc != 2)
        return help();

    unsigned length = convert_to_uint(argv[1]);

#if defined(MEMOIZE) || defined(TABULAR)
    init_table(length);
#endif

    int prices[length];
    get_prices(prices, length);

    int result = rod_cutting(prices, length);

    printf("\nMaxmimum sale price for rod of length %d: %d\n", length, result);

#if defined(MEMOIZE) || defined(TABULAR)
    free(TABLE);
#endif
    return 0;
}