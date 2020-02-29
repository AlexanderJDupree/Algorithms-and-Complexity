/*
 * File         : sum_descent.c
 * Description  : Algorithms to calculate the minimum sum descent
 *                down a triangle
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree
*/

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int min(unsigned a, unsigned b)
{
    return (a < b) ? a : b;
}

int min_sum_descent(int* triangle, unsigned rows, unsigned size)
{
    if(rows == 0) { return triangle[0]; }

    int child_row  = size - rows;
    int parent_row = size - rows - rows + 1;
    int diff       = child_row - parent_row;

    for(int i = parent_row; i < child_row; ++i)
    {
        int left_child  = triangle[i + diff];
        int right_child = triangle[i + diff + 1];

        triangle[i] += min(left_child, right_child);
    }
    return min_sum_descent(triangle, rows - 1, size - rows);
}

unsigned long choose(int n, int k)
{
    if(k > n) { return 0; }

    unsigned long table[n + 1][k + 1];

    table[0][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j <= min(i, k); ++j)
        {
            unsigned long left  = (j - 1 < 0) ? 0 : table[i-1][j-1];
            unsigned long right = (j > i - 1) ? 0 : table[i-1][j];

            table[i][j] = left + right;
        }
    }
    return table[n][k];
}

int help()
{
    fprintf(stderr, "\nusage: sum_descent <num>\n");
    return 1;
}

unsigned convert_to_uint(char* arg)
{
    char* endptr = arg;
    long long val = strtoll(arg, &endptr, 0);
    if(*endptr != '\0' || val < 0  || val > UINT32_MAX)
    {
        fprintf(stderr, "\nsum_descent: Fatal, bad input");
        exit(help());
    }
    return val;
}

void fill_triangle(int* triangle, unsigned n)
{
    srand(time(NULL));

    for(int i = 0; i < n; ++i)
    {
        triangle[i] = rand() % 100;
    }
    return;
}

void display_triangle(int* triangle, unsigned rows, unsigned size, int depth)
{
    if(rows == 0) { return; }

    display_triangle(triangle, rows - 1, size - rows, depth + 1);

    for(int i = 0; i < depth * 2; ++i)
    {
        printf(" ");
    }

    for(int i = size - rows; i < size; ++i)
    {
        printf(" %d ", triangle[i]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    if(argc != 2)
        return help();

    unsigned rows = convert_to_uint(argv[1]);

    unsigned size = choose(rows + 1, 2);

    printf("\nrows: %u\nsize: %u\n\n", rows, size);

    int triangle[size];

    fill_triangle(triangle, size);

    display_triangle(triangle, rows, size, 0);

    int result = min_sum_descent(triangle, rows, size);

    printf("\nMinimum Sum Descent: %d\nResulting Triangle:\n\n", result);

    display_triangle(triangle, rows, size, 0);
    
    return 0;
}
