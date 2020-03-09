
// YOUR NAME: Alexander DuPree

// Kruskal's Algorithm Lab

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
         // for qsort
#include <unistd.h>
         // for usleep




#define INF  1000000
   // infinity

// The adjacency matrix for the graph :
int N ; // number of nodes (vertices)
int A[100][100] ; // adjacency matrix of the graph


int input_graph()
{
  int r,c ;
  char w[10] ;

  scanf("%d",&N) ;
  
  // scan the first row of labels....not used
  for (c = 0 ; c < N ; c++) {
    scanf("%s",w) ;
  }
  

  for (r = 0 ; r < N ; r++) {
    scanf("%s",w) ; // label ... not used
    for (c = 0 ; c < N ; c++) {
      scanf("%s",w) ;
      if (w[0] == '-') {
	A[r][c] = -1 ;
      } else {
	A[r][c] = atoi(w) ;// ascii to integer
      }
      
    }
  }
  
}




int print_graph()
{
  int r,c ;

  printf("\n%d\n\n",N) ;
  
  printf("  ") ;
  for (c = 0 ; c < N ; c++) {
    printf("   %c",c+'A') ;
  }
 
  printf("\n") ;  
  
  for (r = 0 ; r < N ; r++) {
    printf("%c  ",r+'A') ;
    for (c = 0 ; c < N ; c++) {
      if (A[r][c] == -1) {
	printf("  - ") ;
      } else {
	printf("%3d ",A[r][c]) ;
      }
    }
    printf("\n") ;
  }
  printf("\n") ;  
}






typedef
struct {
  int vstart ;
  int vend ;
  int vlen ;
}
Edge ;

Edge elist[100] ;

int compare (const void *p1,  const void *p2)
{
  Edge *a, *b ;
  a = (Edge *) p1 ;
  b = (Edge *) p2 ;
  if ((*a).vlen < (*b).vlen) {
    return -1 ;
  } else if ((*a).vlen > (*b).vlen) {
    return 1 ;
  } else {
    return 0 ;
  }
}

void merge(Edge* list, int lo, int mid, int hi)
{
  int i = 0;
  Edge temp[hi - lo + 1];

  int lf = lo;
  int rf = mid + 1;
  while(lf <= mid && rf <= hi)
  {
    temp[i++] = compare(&list[lf], &list[rf]) < 0 ? list[lf++] : list[rf++];
  }

  // Merge the rest, Only one of these while loops will execute
  while(lf <= mid)
  {
    temp[i++] = list[lf++];
  }
  while(rf <= hi)
  {
    temp[i++] = list[rf++];
  }

  // Copy back into ara
  for(--i; hi >= lo; --hi)
  {
    list[hi] = temp[i--];
  }
  return;
}

void merge_sort(Edge* list, int lo, int hi)
{
  if(lo >= hi)
  {
    return;
  }

  int mid = (lo + hi) / 2;

  merge_sort(list, lo, mid);
  merge_sort(list, mid + 1, hi);

  merge(list, lo, mid, hi);
}



int  print_edge_list(Edge *elist, int N)
{
  int i ;
  printf("\n") ;  
  for (i = 0 ; i < N ; i++) {
    printf("<%c, %c, %d> ",
	   'A'+elist[i].vstart, 'A'+elist[i].vend,elist[i].vlen) ;
  }
  printf("\n") ;
}


int print_array(int *x, int n)
{
  int i ;
  for (i = 0 ; i < n ; i++) {
    printf(" %3d",x[i]) ;
  }  
}

int find(int* disjoint, int i)
{
  if(disjoint[i] == -1)
    return i;
  
  return find(disjoint, disjoint[i]);
}

void set_union(int* disjoint_set, int s1, int s2)
{
  int s1_root = find(disjoint_set, s1);
  int s2_root = find(disjoint_set, s2);

  if(s1_root != s2_root)
    disjoint_set[s1_root] = s2_root;
}

int kruskal()
{
  // a tree has the property that |E| = |V| - 1
  
  // 1 .make a list of all edges
  // 2. sort this list (FOR FULL CREDIT use a time 
  //    complexity n*log(n) sorting algorithm discussed in class)
  // 3. starting with the shortest edge in the sorted list and
  // continuing until you have N -1 edges (or realize that you can't)
  // adjoin this edge to your potential tree list unless it would
  // create a cyle.

  // assume an undirected graph, hence only need the upper right
  // part of the adjacency matrix :

  // code below creates and then prints array of edges
  
  int e,r,c ;
  
  e = 0 ; // number of edges
  for (r = 0 ; r < N ; r++) {
    for (c = r+1 ; c < N ; c++) {
      if (A[r][c] != -1) {
        elist[e].vstart = r ; // start vertex of edge
        elist[e].vend = c ; // end vertex of edge
        elist[e].vlen = A[r][c] ;
        e++ ;
      }
    }
  }
  
  if (e < N-1) {
    printf("there aren't enough edges to build a spanning tree\n") ;
    return 0 ;
  }
  
  print_edge_list(elist, e) ;
  
  //  YOUR CODE GOES BELOW! 
  //  Note:  this function should call print_edge_list() at the 
  //         end to give the edges in a minimum spanning tree

  merge_sort(elist, 0, e - 1);

  int edge_index = 0;
  Edge mst[N]; // Minimum Spanning Tree

  int disjoint_set[N-1];
  for(int i = 0; i < N; ++i)
  { // Init disjoint set array
    disjoint_set[i] = -1;
  }

  for(int i = 0; edge_index < N-1 && i < e; ++i)
  {
    int s1 = find(disjoint_set, elist[i].vstart);
    int s2 = find(disjoint_set, elist[i].vend);

    if(s1 != s2) // No cycle detected
    {
      mst[edge_index++] = elist[i];
      set_union(disjoint_set, s1, s2);
    }
    // Cycle detected, discard Edge
  }

  printf("\n\nResulting Minimum Spanning Tree:\n");
  print_edge_list(mst, N-1);
  
  return 0;
}



int main()
{
  // Before modifying this skeleton, try compiling and then
  // try running with ./a.out < graph08.input
  input_graph() ;// N, A{}{}  
  print_graph() ;
  kruskal() ;
}

