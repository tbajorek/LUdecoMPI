#include "../include/LU.h"
#include <stdio.h>

#ifdef METHOD_MPI

void updateColumn(vector* c, vector* l, int k) {
    int i;
    for (i = k+1; i <= c->size; i++){
        setVecValue(c, i, getVecValue(c, i) - getVecValue(l, i) * getVecValue(c, k));
    }
}

matrix* decompose(matrix* m) {
    matrix *m2 = copyMatrix(m);
    int j,k,s;
    vector* column;
    vector* kcolumn;
    for(k=1; k <= m2->cols-1; k++){
        // STEP 1
        for (s=k+1; s <= m2->rows; s++) {
            setMatValue(m2, s, k, getMatValue(m2, s, k)/getMatValue(m2, k, k));
        }
        // STEP 2
        kcolumn = getColumn(m2, k);
        for (j = k+1; j <= m2->cols; j++) {
            column = getColumn(m2, j);
            updateColumn(column, kcolumn, k);
            setColumn(m2, column, j);
            freeVector(column);
        }
        freeVector(kcolumn);
    }
    return m2;
}

#endif