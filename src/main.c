/*
 * File:   maina.c
 * Author: tomek
 *
 * Created on 4 kwietnia 2017, 03:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/LU.h"

int main(int argc, char** argv) {
    matrix *m, *m2;
    env e = init(argc, argv);
    if (e.myid == 0) {
        m = zeroMatrix(6,6);
        const double input[6][6]={
            3,4,7,8,1,6,
            2,5,8,1,5,9,
            3,6,9,7,8,9,
            5,4,3,9,5,8,
            3,9,1,8,5,4,
            4,2,8,4,7,5
        };
        int i,j;
        for(i=1; i <= m->rows; i++){
          for(j=1; j <= m->cols; j++){
            setMatValue(m,i,j,input[i-1][j-1]);
          }
        }

        printf("----------Poczatkowa macierz m----\n");
        displayMatrix(m);

        printf("--------------\n");
    } else {
        m = ghostMatrix(6,6);
    }
    m2 = decompose(m, e);
    
    if (e.myid == 0) {
        printf("----------Koncowa macierz m2----\n");
        displayMatrix(m2);
    }
    freeMatrix(m2);
    freeMatrix(m);
    
    return (EXIT_SUCCESS);
}

/**
 LU:
 3.000000	4.000000	7.000000	8.000000	1.000000	6.000000	
 0.666667	2.333333	3.333333	-4.333333	4.333333	5.000000	
 1.000000	0.857143	-0.857143	2.714286	3.285714	-1.285714	
 1.666667	-1.142857	5.666667	-24.666667	-10.333333	11.000000	
 1.000000	2.142857	15.333333	1.310811		-42.121622	-7.418919	
 1.333333	-1.428571	-4.000000	0.081081		-0.613410	-6.442733	
 */