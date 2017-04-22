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
    matrix* m = zeroMatrix(3,3);
    const double input[3][3]={
        3,4,7,
        2,5,8,
        3,6,9
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
    matrix* m2 = decompose(m);
    
    printf("----------Koncowa macierz m2----\n");
    displayMatrix(m2);
    
    freeMatrix(m2);
    freeMatrix(m);
    return (EXIT_SUCCESS);
}

/**
 LU:
 3.000000	4.000000	7.000000	
 0.666667	2.333333	3.333333	
 1.000000	0.857143	-0.857143	
 */