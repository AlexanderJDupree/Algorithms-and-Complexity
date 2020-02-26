/*
 * File         : dupree_a_lab5.c
 * Description  : Implement a smart search pattern matcher
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Find the location of the first occurrence of pattern in text
// or say that it does not occur if that is the case.
// If you find the pattern in the text, output the index of the
// first letter in text where the pattern first occurs.

// You must also print the total number of character compairsons that
// the program made.

// If the number of unchecked characters in the text is ever less than
// the length of the pattern the algorithm must stop.

// NOTE:  All test texts and patterns should not contain any white space
//        (e.g. blank space character, newline, tab, etc.) as scanf
//        will stop on such an input character.

#define ASCII_CHARS 128

typedef struct __result {
  int index;
  int occurences;
  int comparisons;
} Result;

void init_shift_array(int pSize, const char* pattern, int* shift_width)
{
  // Init all element to pSize;
  for(int i = 0; i < ASCII_CHARS; ++i)
  {
    shift_width[i] = pSize;
  }

  shift_width[(int) pattern[pSize - 1]] = pSize--;

  for(int i = 0; pSize > 0; --pSize)
  {
    shift_width[(int) pattern[i++]] = pSize;
  }
}

Result smart_search(int pSize, const char* pattern, int tSize, const char* text)
{
  // index is set to -1, indicating failure
  Result results = { -1, 0, 0 };

  if(pSize < tSize)
  {
    unsigned SM = pSize - 1;
    unsigned pIndex = pSize - 1;
    int shift_width[ASCII_CHARS];

    init_shift_array(pSize, pattern, shift_width);

    for (int i = SM; SM < tSize; ++results.comparisons)
    {
      if(text[i] != pattern[pIndex]) // Reject substring
      {
        // Move Start Marker right based on index value of char
        SM += shift_width[(int) text[SM]];

        // Reset indices
        pIndex = pSize - 1; 
        i = SM;
      }
      else if(pIndex == 0) // Substring matched
      {
        // Only store index of first occurence
        if(results.index == -1)
        {
          results.index = i;
        }

        ++results.occurences;

        SM += pSize; // Jump to next substring segment

        // Reset indices
        pIndex = pSize - 1; 
        i = SM;
      }
      else // Characters matched, continue to scan substring
      {
        --i;
        --pIndex;
      }
    }
  }

  return results;
}

int main()
{
  char text[10000] ;
  char pattern[200] ;
  int tSize, pSize;

  printf("enter text : ") ;
  scanf("%s", text) ;
  printf("enter pattern you are searching for : ") ;
  scanf("%s", pattern) ;

  pSize = strlen(pattern) ;
  tSize = strlen(text) ;
  printf("The pattern has %d characters and the text has %d characters.\n", pSize,tSize);

  Result results = smart_search(pSize, pattern, tSize, text);

  printf("\nOccurences: %d\nIndex of First Occurence: %d\nComparisons: %d\n"
        , results.occurences
        , results.index
        , results.comparisons
        );

  return 0;
}
