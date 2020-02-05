/*
 * File         : dupree_a_lab3a.c
 * Description  : Implement quick sort and driver program
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree1
*/

#include <stdio.h>
#include <stdlib.h>

/* Utility Functions */
int read_int(); 
void fill_array(int* ara, unsigned size);
void display_array(int* ara, unsigned size);

/* Assignment */
void swap(int* a, int* b);
void partition_sort(int* ara, int left, int right);
int  partition(int* ara, int left, int right);

int main()
{
  printf("\nEnter size of array: ");
  int n = read_int();

  int list[n];

  fill_array(list, n);

  printf("\n\nBefore Sorting: ");
  display_array(list, n);

  partition_sort(list, 0, n - 1);

  printf("\nAfter Sorting: ");
  display_array(list, n);

  return 0;
}

void partition_sort(int* ara, int left, int right)
{
  if(left >= right) { return; } // Base Case

  int part = partition(ara, left, right);

  partition_sort(ara, left, part - 1);
  partition_sort(ara, part + 1, right);
}

int partition(int* ara, int left, int right)
{
  int pivot = left++;

  while(left < right)
  {
    // Scan right, searching for elements greater than pivot
    while(ara[left] <= ara[pivot] && left < right) { ++left; }

    // Scan left, searching for elements less than pivot
    while(ara[right] > ara[pivot]) { --right; }

    // Arrange items around the pivot
    if(left < right)
      swap(ara + left, ara + right);
  }

  // Put pivot in rightmost spot with item less than pivot
  swap(ara + pivot, ara + right);
  return right;
}

void swap(int* a, int* b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
  return;
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
