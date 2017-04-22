#include "../include/LU.h"
#include <stdio.h>

#ifdef METHOD_SEQ

matrix* decompose(matrix* m, int argc, char** argv) {
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

#endif