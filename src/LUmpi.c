#include "../include/LU.h"
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#ifdef METHOD_MPI

#define KCOLUMN 1
#define COL2UPDATE 2

void updateColumn(vector* c, vector* l, int k) {
    int i;
    for (i = k+1; i <= c->size; i++){
        setVecValue(c, i, getVecValue(c, i) - getVecValue(l, i) * getVecValue(c, k));
    }
}

MPI_Datatype* createMpiDatatypeForVector(int size) {
    MPI_Datatype* datatype = (MPI_Datatype*)malloc(sizeof(MPI_Datatype));
    int counts[2] = { size, 1 };
    MPI_Datatype types[2] = { MPI_DOUBLE, MPI_INT};
    MPI_Aint displs[2] = {
        offsetof(vector, values),
        offsetof(vector, size),
    };
    MPI_Type_create_struct(1, counts, displs, types, datatype);
    MPI_Type_commit(datatype);
    return datatype;
}

int getProcIdByColumn(int column, int numprocs) {
    return column%(numprocs-1)+1;
}

matrix* decompose(matrix* m, int argc, char** argv) {
    int n, myid, numprocs, procit;
    matrix *m2;
    int j,k,s;
    vector* column;
    vector *kcolumn, *recvKcolumn, *recvColumn;
    MPI_Datatype* vectorType;
    MPI_Status status;
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    vectorType = createMpiDatatypeForVector(m->rows);
    m2 = copyMatrix(m);
    
    for(k=1; k <= m2->cols-1; k++){
        if (myid == 0) {
            // STEP 1
            for (s=k+1; s <= m2->rows; s++) {
                setMatValue(m2, s, k, getMatValue(m2, s, k)/getMatValue(m2, k, k));
            }
            // STEP 2
            kcolumn = getColumn(m2, k);
            for (procit = 1; procit < numprocs; ++procit) {
                MPI_Send(kcolumn->values, kcolumn->size, MPI_DOUBLE, procit, KCOLUMN, MPI_COMM_WORLD);
            }
            freeVector(kcolumn);
        }
        /*for (j = k+1; j <= m2->cols; j++) {
            if (myid == 0) {
                column = getColumn(m2, j);
                MPI_Send(column, 1, vectorType, getProcIdByColumn(j, numprocs), COL2UPDATE, MPI_COMM_WORLD);
                MPI_Recv(column, 1, vectorType, MPI_ANY_SOURCE, COL2UPDATE, MPI_COMM_WORLD, &status );
                setColumn(m2, column, column->id);
                freeVector(column);
            } else {
                MPI_Recv(recvKcolumn, 1, vectorType, MPI_ANY_SOURCE, KCOLUMN,MPI_COMM_WORLD, &status );
                MPI_Recv(recvColumn, 1, vectorType, MPI_ANY_SOURCE, COL2UPDATE,MPI_COMM_WORLD, &status );
                updateColumn(recvColumn, recvKcolumn, recvKcolumn->id);
                MPI_Send(column, 1, vectorType, getProcIdByColumn(j, numprocs), COL2UPDATE, MPI_COMM_WORLD);
            }
        }*/
        
    }
    
    MPI_Type_free(vectorType);
    MPI_Finalize();
    return m2;
}

#endif