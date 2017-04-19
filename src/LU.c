#include "../include/LU.h"
#include "../include/utils.h"
#include <stdio.h>
matrix* decompose(matrix* m) {
  int numOfCol = m->cols;
  int numOfRows = m->rows;
  matrix *m2 = copyMatrix(m);
  int i,j,k,s;
  for(k=0; k<numOfCol-1; k++){
    // STEP 1
    for ( s=k+1 ;s <numOfRows ; s++) {
      m2->values[s][k] = m2->values[s][k]/m2->values[k][k];
    }
    // STEP 2
    for (i = k+1 ;i <numOfCol ; i++) {
      for (j = k+1; j <numOfRows ; j++){
        m2->values[i][j] = m2->values[i][j] - m2->values[i][k]*m2->values[k][j];
      }
    }
  }
  return m2;
}
