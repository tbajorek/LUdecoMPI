#include "../include/LU.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"

#ifdef METHOD_MPI

#define KCOLUMN 1
#define COL2UPDATE 2

#define SEND_COLUMN 0
#define RECEIVE_COLUMN 1

void updateColumn(vector* c, vector* l, int k) {
    int i;
    for (i = k+1; i <= c->size; i++){
        setVecValue(c, i, getVecValue(c, i) - getVecValue(l, i) * getVecValue(c, k));
    }
}

void sendColumn(vector* column, int procid) {
    MPI_Send(&column->size, 1, MPI_INT, procid, 1, MPI_COMM_WORLD);
    MPI_Send(column->values, column->size, MPI_DOUBLE, procid, 2, MPI_COMM_WORLD);
    MPI_Send(&column->id, 1, MPI_INT, procid, 3, MPI_COMM_WORLD);
}

env init(int argc, char** argv) {
    env e;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&e.numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&e.myid);
    return e;
}

vector* receiveColumn(MPI_Status *status) {
    int size;
    vector* column;
    MPI_Recv(&size, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, status);
    column = createVector(size);
    MPI_Recv(column->values, size, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, status);
    MPI_Recv(&column->id, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, status);
    return column;
}

int getProcIdByColumn(int column, int numprocs) {
    return column%(numprocs-1)+1;
}

matrix* decompose(matrix* m, env e) {
    int n, procit;
    matrix *m2;
    int j,k,s;
    vector *column, *kcolumn, *recvKcolumn, *recvColumn;
    MPI_Status status;
    int cols = m->cols;
    int myid = e.myid, numprocs = e.numprocs;
    if (myid == 0) {
        m2 = copyMatrix(m);
    } else {
        m2 = ghostMatrix(m->rows, m->cols);
    }
    for(k=1; k <= cols-1; k++){
        if (myid == 0) {
            // STEP 1
            for (s=k+1; s <= m2->rows; s++) {
                setMatValue(m2, s, k, getMatValue(m2, s, k)/getMatValue(m2, k, k));
            }
            kcolumn = getColumn(m2, k);
            for (procit = 1; procit < numprocs; ++procit) {
                sendColumn(kcolumn, procit);
            }
            freeVector(kcolumn);
        } else {
            recvKcolumn = receiveColumn(&status);
        }
        // STEP 2
        for (j = k+1; j <= cols; j++) {
            if (myid == 0) {
                column = getColumn(m2, j);
                sendColumn(column, getProcIdByColumn(j, numprocs));
                freeVector(column);
                column = receiveColumn(&status);
                setColumn(m2, column, column->id);
                freeVector(column);
            } else if (myid == getProcIdByColumn(j, numprocs)) {
                recvColumn = receiveColumn(&status);
                updateColumn(recvColumn, recvKcolumn, recvKcolumn->id);
                sendColumn(recvColumn, 0);
                freeVector(recvColumn);
            }
        }
        if (myid != 0) {
            freeVector(recvKcolumn);
        }
    }
    MPI_Finalize();
    return m2;
}

#endif
