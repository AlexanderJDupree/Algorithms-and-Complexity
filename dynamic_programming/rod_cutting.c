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

int max(int* sales, unsigned length)
{
    int m = sales[0];
    int unit = 0;
    for(int i = 1; i < length; ++i)
    {
        if(sales[i] > m) 
        { 
            m = sales[i]; 
        }
    }
    return m;
}

int rod_cutting(int* prices, unsigned length)
{
    int sales[length];

    sales[length-1] = prices[length];

    for(int i = 0; i < length - 1; ++i)
    {
        sales[i] = rod_cutting(prices, i + 1);
    }
    return max(sales, length);
}

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

void get_prices(int* prices, unsigned n)
{
    char buffer[1024];

    prices[0] = 0;
    for (size_t i = 1; i <= n; ++i)
    {
        printf("\nEnter Price for unit of length %lu: ", i);
        scanf("%s", buffer);
        prices[i] = convert_to_uint(buffer);
    }
}

void init_array(int* result, unsigned size, int initializer)
{
    if(size <= 0) { return; }

    result[--size] = initializer;

    return init_array(result, size, initializer);
}

int main(int argc, char** argv)
{
    if(argc != 2)
        return help();

    unsigned length = convert_to_uint(argv[1]);

    int prices[length + 1];
    get_prices(prices, length);

    int result = rod_cutting(prices, length);

    printf("\nMaxmimum sale price for rod of length %d: %d\n", length, result);
    return 0;
}