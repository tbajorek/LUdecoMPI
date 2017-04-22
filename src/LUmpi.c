#include "../include/LU.h"
#include <stdio.h>
#include "mpi.h"

#ifdef METHOD_MPI

void updateColumn(vector* c, vector* l, int k) {
    int i;
    for (i = k+1; i <= c->size; i++){
        setVecValue(c, i, getVecValue(c, i) - getVecValue(l, i) * getVecValue(c, k));
    }
}

matrix* decompose(matrix* m, int argc, char** argv) {
    int n, myid, numprocs;
    matrix *m2;
    int j,k,s;
    vector* column;
    vector* kcolumn;
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    m2 = copyMatrix(m);
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
    MPI_Finalize();
    return m2;
}

#endif