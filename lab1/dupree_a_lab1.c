/*
 * File         : dupree_a_lab1.c
 * Description  : Implement an iterative and recurisve power algorithm
 * Class        : CS350.001 WI 2020
 * Author       : Alexander DuPree1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

double my_power(double x, int n)
// O(n)
{
    double res = 1;
    for (int i = 0; i < n; ++i)
    {
        res *= x;
    }
    return res;
}

double my_recursive_power(double x, int n)
// O(log(n))
{
    if (n == 0) { return 1; } // Base Case

    double res = my_recursive_power(x, n/2);

    // If the exponent is odd we need to multiply the base one more time
    return (n % 2 == 0) ? res * res : res * res * x;
}


// begin TIMING variables
int signal ;
struct timeval Tp;
struct timezone Tzp ;
long sec,usec ;
double dsec1, dsec2 ;
// end TIMING variables


void begin_timing()
{
  signal = gettimeofday(&Tp,&Tzp) ;
  usec = Tp.tv_usec ;
  sec = Tp.tv_sec ;
  dsec1 = sec + usec/1000000.0 ;
}
  
void end_timing()
{
  signal = gettimeofday(&Tp,&Tzp) ;
  usec = Tp.tv_usec ;
  sec = Tp.tv_sec ;
  dsec2 = sec + usec/1000000.0 ;
}






int test01(int n)
{
  int numreps,i ;

  printf("\n===================================================\n") ;
  printf("Exponent = %d\n",n) ;
  numreps = 10000000 ; // ten million
  printf("numreps = %d\n",numreps) ;
  printf("\n") ;
  
  //======================================================================
  printf("obvious power algorithm : \n") ;
  //======================================================================

  double x,p;
  
  begin_timing() ;
  srandom(100) ;
  for (i = 0 ; i < numreps ; i++) {
    x = 2*drand48() ;
    p = my_power(x,n) ;
    //  printf("%e\n",p) ;
  }
  end_timing() ;
  printf("Total time of %d reps is %18lf seconds\n",numreps, dsec2 - dsec1) ;
  printf("Average time took %e seconds.\n", (dsec2 - dsec1)/numreps) ;


  
  //======================================================================
  printf("recursive power algorithm : \n") ;
  //======================================================================

  
  begin_timing() ;
  srandom(100) ;
  for (i = 0 ; i < numreps ; i++) {
    x = 2*drand48() ;
    p = my_recursive_power(x,n) ;
    //  printf("%e\n",p) ;
  }
  end_timing() ;
  printf("Total time of %d reps is %18lf seconds\n",numreps, dsec2 - dsec1) ;
  printf("Average time took %e seconds.\n", (dsec2 - dsec1)/numreps) ;  
  

  return 0;
}



int main()
{
  printf("%lf %lf %lf\n",pow(2.5,14), my_power(2.5, 14), my_recursive_power(2.5,14)) ;

  test01(100) ;
  test01(1000) ;      

  printf("pow(0,0) = %lf", pow(0,0));

  return 0;
}
