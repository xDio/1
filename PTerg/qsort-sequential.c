/**********************************************************************
 *
 * qsort-sequential.c -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/

#include <pthread.h>
#include <stdio.h>
#include "qsort-sequential.h"

/* swap -- swap elements k and l of vector v */
void swap(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}


/* partition -- in-place update of elements */
int partition(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;
  
  for (int j = 0; j < n - 1; j++) 
    if (v[j] < pivot) 
      swap(v,i++,j);

  swap(v, i, n - 1);
  return (i);
}

/* qsortseq -- Entry point for QuickSort */
void sort_seq(int *v, int n) {

  if (n > 1) {
    int p = partition(v, n);
    sort_seq(v,p);
    sort_seq(&v[p+1],n-p-1);
  }
}


pthread_mutex_t mux;

/* qsortseq -- Entry point for QuickSort */
void *qsort_seq( void *arg) {
  int *v, n, maxt;
  v = ( ( parg * ) arg ) -> adr;
  n = ( ( parg * ) arg ) -> size;
  maxt = ( ( parg * ) arg ) -> numt;
  
  if (n>1){
  if (c<maxt && maxt!=1) {
    int p = partition(v, n);
    
	pthread_mutex_lock(&mux);
	c+=2;
    pthread_mutex_unlock(&mux);
	
	pthread_t thread1;
	pthread_t thread2;
	
	parg arg1;
	parg arg2;
	
	arg1.size = p;
    arg1.adr = v;
	arg2.size = n-p-1;
    arg2.adr = &v[p+1];	
	
	pthread_create( &thread1, NULL, qsort_seq, &arg1 );
    pthread_create( &thread2, NULL, qsort_seq, &arg2 );
	
	pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );
	
	pthread_mutex_lock(&mux);
    c-=2;
    pthread_mutex_unlock(&mux);
  }
  else {
	  sort_seq(v, n);
    }
 }
 }



