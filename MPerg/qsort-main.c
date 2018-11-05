/**********************************************************************
 *
 * qsort.c -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-sequential.h"
#include <assert.h>
#include <omp.h>

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);

/* --- Entry POINT --- */
int main(int argc, char **argv) {

  /* parse input */
  if (argc != 3) {
    printf("Usage: %s q p\n  where n=2^q is problem size (power of two)\n and t=2^p is the number of maximum threads", 
	   argv[0]);
    exit(1);
  }
  
  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double seq_time;
  
  /* initiate vector of random integerts */
  int n  = 1<<atoi(argv[1]);
  int *a = (int *) malloc(n * sizeof(int));
  int p = 1<<atoi(argv[2]);
  
  /* initialize vector */
  init(a, n);

  /* print vector */
  /* print(a, n); */

  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  omp_set_num_threads(p);
  #pragma omp parallel
    {
      #pragma omp single
      {
        qsort_seq(a, n);
      }
    }
  
  gettimeofday (&endwtime, NULL);

  /* get time in seconds */
  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  int pass = test(a, n);
  printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
  assert( pass != 0 );
 
  /* print sorted vector */
  /* print(a, n); */

  /* print execution time */
  printf("Sequential wall clock time: %f sec\n", seq_time);

  /* exit */
  return 0;
  
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  // TODO: implement
  for (int i = 0; i < n-1; i++) {
    if (*(a + i +1) < *(a + i)) {
      return 0;
    } 
  }
   
  return 1;
  
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
