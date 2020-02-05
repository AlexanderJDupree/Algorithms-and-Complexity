/*
 * File         : dupree_a_lab3a.c
 * Description  : Implement a merge sort and driver program
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree1
*/

#include <stdio.h>
#include <stdlib.h>

int read_int(); 
void fill_array(int* ara, unsigned size);
void display_array(int* ara, unsigned size);

void merge_sort(int* ara, int lo, int hi);

int main()
{
  printf("\nEnter size of array: ");
  int n = read_int();

  int list[n];

  fill_array(list, n);

  printf("\n\nBefore Sorting: ");
  display_array(list, n);

  merge_sort(list, 0, n - 1);

  printf("\nAfter Sorting: ");
  display_array(list, n);

  return 0;
}

void merge(int* ara, int lo, int mid, int hi)
{
  int i = 0;
  int temp[hi - lo + 1];

  int lf = lo;
  int rf = mid + 1;
  while(lf <= mid && rf <= hi)
  {
    temp[i++] = (ara[lf] < ara[rf]) ? ara[lf++] : ara[rf++];
  }

  // Merge the rest, Only one of these while loops will execute
  while(lf <= mid)
  {
    temp[i++] = ara[lf++];
  }
  while(rf <= hi)
  {
    temp[i++] = ara[rf++];
  }

  // Copy back into ara
  for(--i; hi >= lo; --hi)
  {
    ara[hi] = temp[i--];
  }
  return;
}

void merge_sort(int* ara, int lo, int hi)
{
  if(lo >= hi)
  {
    return;
  }

  int mid = (lo + hi) / 2;

  merge_sort(ara, lo, mid);
  merge_sort(ara, mid + 1, hi);

  merge(ara, lo, mid, hi);
}


int read_int()
{
  int n;
  while(scanf("%d", &n) == 0)
  {
    printf("\nerror: enter a valid number: ");
    while ((getchar()) != '\n'); // discard characters in buffer
  }
  return n;
}

void fill_array(int* ara, unsigned size)
{
  for(int i = 0; i < size; ++i)
  {
    printf("\nEnter data for entry %d: ", i);
    ara[i] = read_int();
  }
  return;
}

void display_array(int* ara, unsigned size)
{
  printf("\n[");
  for(int i = 0; i < size - 1; ++i)
  {
    printf("%d, ", ara[i]);
  }
  printf("%d]\n", ara[size - 1]);
}
