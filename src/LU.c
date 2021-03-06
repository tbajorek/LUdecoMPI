#include "LU.h"
#include <stdio.h>

#ifdef METHOD_SEQ

env init(int argc, char** argv) {
    printf("METHOD_SEQ type enabled.\n");
    env e;
    e.myid = 0;
    e.numprocs = 1;
    return e;
}

void sendDimensions(int* rows, int* cols, env e) {}
void receiveDimensions(int* rows, int* cols) {}

matrix* decompose(matrix* m, env e) {
    matrix *m2 = copyMatrix(m);
    int i,j,k,s;
    for(k=1; k <= m->cols-1; k++){
        // STEP 1
        for (s=k+1; s <= m->rows; s++) {
            setMatValue(m2, s, k, getMatValue(m2, s, k)/getMatValue(m2, k, k));
        }
        // STEP 2
        for (i = k+1; i <= m->cols; i++) {
            for (j = k+1; j <= m->rows; j++){
                setMatValue(m2, i, j, getMatValue(m2, i, j) - getMatValue(m2, i, k) * getMatValue(m2, k, j));
            }
        }
    }
    return m2;
}

void finish() {}

#endif
