/*
 * File         : pebbles.c
 * Description  : Algorithms to calculate the maximum number of pebbles that 
 *                that can be collected on any lattice path 
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

#if defined(MEMOIZE) || defined(TABULAR)
// Main must initialize this table before calling pebbles
int** TABLE = NULL;
#endif 

#if defined(MEMOIZE)

int pebbles(int i, int j, int** graph)
{
    if(i < 0 || j < 0) { return 0; }

    if(TABLE[i][j] < 0)
    {
        TABLE[i][j] = graph[i][j] + max( pebbles(i, j-1, graph)
                                       , pebbles(i-1, j, graph) );
    }
    return TABLE[i][j];
}
#elif defined(TABULAR)

int pebbles(int i, int j, int** graph)
{
    /* Calculates the maximum number of pebbles that can be collected on
    any lattice path. 

    Preconditions:
      graph must be correctly initialized and each element on the graph 
      is either a 1 (has a pebble) or a 0 (does not have a pebble). 

      i and j are not bounds checked and it is assumed that graph[i][j]
      is a valid entry on the graph. 
    */

    if(TABLE[i][j] < 0)
    {
        for(int n = 0; n <= i; ++n)
        {
            for(int m = 0; m <= j; ++m)
            {
                int up   = (n > 0) ? TABLE[n-1][m] : 0;
                int left = (m > 0) ? TABLE[n][m-1] : 0;

                TABLE[n][m] = graph[n][m] + max(up, left);
            }
        }
    }
    return TABLE[i][j];
}
#else
int pebbles(int i, int j, int** graph)
{
    if(i < 0 || j < 0) { return 0; }

    return graph[i][j] + max( pebbles(i, j-1, graph)
                            , pebbles(i-1, j, graph));
}
#endif 

int** init_graph(int n, int m, int initializer)
{
    int** graph = malloc(n * sizeof(int*));
    for(int i = 0; i < n; ++i)
    {
        graph[i] = malloc(m * sizeof(int));
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            graph[i][j] = initializer;
        }
    }

    return graph;
}

void free_graph(int** graph, int n)
{
    for(int i = 0; i < n; ++i)
    {
        free(graph[i]);
    }
    free(graph);
}

void fill_pebbles(int** graph, int n, int m, int num_pebbles)
{
    srand(time(NULL));

    // Prevent infinite loop
    if(num_pebbles > n * m) { num_pebbles = n*m; }

    while(num_pebbles > 0)
    {
        int i = rand() % n;
        int j = rand() % m;

        // Limit to one pebble per entry
        if(!graph[i][j])
        {
            ++graph[i][j];
            --num_pebbles;
        }
    }
}

void print_border(int cols)
{
    printf("+");
    for(int i = 0; i < cols; ++i)
    {
        printf("--");
    }
    printf("+\n");
}

void display_graph(int** graph, int n, int m) {
    for(int i = 0; i < n; ++i)
    {
        print_border(m);
        for(int j = 0; j < m; ++j)
        {
            printf("|%d", graph[i][j]);
        }
        printf(" |\n");
    }
    print_border(m);
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("\npebbles: <n> <m> [options]\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int num_pebbles = 5;
    if(argc == 4)
    {
        num_pebbles = atoi(argv[3]);
    }

    int** graph = init_graph(n, m, 0);
    fill_pebbles(graph, n, m, num_pebbles);

#if defined(MEMOIZE) || defined(TABULAR)
    TABLE = init_graph(n, m, -1);
#endif 

    display_graph(graph, n, m);

    int result = pebbles(n-1, m-1, graph);

    printf("\nMax number of pebbles to possibly collect: %d\n", result);

    free_graph(graph, n);

#if defined(MEMOIZE) || defined(TABULAR)
    free_graph(TABLE, n);
#endif 
    return 0;
}