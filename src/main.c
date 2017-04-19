/*
 * File:   maina.c
 * Author: tomek
 *
 * Created on 4 kwietnia 2017, 03:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

/*
 *
 */
int main(int argc, char** argv) {
  // vector* vv = zeroVector(100);
  // displayVector(vv);
  // freeVector(vv);
    matrix* m = zeroMatrix(3,3);
    double input[3][3]={3,4,7, 2,5,8, 3,6,9};
    int i,j;
    for(i=1;i <= m->rows; i++){
      for(j=1;j <= m->cols; j++){
        setMatValue(m,i,j,input[i-1][j-1]);
      }
    }
    // setMatValue(m,3,2,22);
    // printf("value:%f\n",getMatValue(m,3,2));
    // setMatValue(m,1,1,10);
    // setMatValue(m,2,3,4);
    // setMatValue(m,3,2,7);
    printf("----------Poczatkowa macierz m----\n");
    displayMatrix(m);
    //writeToFile("bin/test.txt", m);
    //m2 = readFromFile("bin/test.txt");
    //displayMatrix(m2);
    printf("--------------\n");
   matrix* m2 = decompose(m);
   printf("----------Koncowa macierz m2----\n");
   displayMatrix(m2);
   freeMatrix(m2);
    freeMatrix(m);
    return (EXIT_SUCCESS);
}
