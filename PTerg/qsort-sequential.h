/**********************************************************************
 *
 * qsort-sequential.h -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/


#ifndef _QSORT_SEQUENTIAL_H_
#define _QSORT_SEQUENTIAL_H_

/* qsortseq -- Sort vector v (of length n) using QuickSort */
void *qsort_seq( void *arg);

typedef struct{
    int size, numt, *adr;
} parg;
int c=0;

#endif /* _QSORT-SEQUENTIAL_H_ */



