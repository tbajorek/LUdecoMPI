#include "LU.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"
#include "mpe.h"
#ifdef METHOD_MPI

#ifdef MPE_LOGS
#include "mpe_utils.h"
#endif

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
#ifdef MPE_LOGS
    MPE_Log_event( START_SEND_COLUMN_SIZE, 0 , "START_SEND_COLUMN_SIZE");
#endif
    MPI_Send(&column->size, 1, MPI_INT, procid, 1, MPI_COMM_WORLD);
#ifdef MPE_LOGS
    MPE_Log_event( END_SEND_COLUMN_SIZE, 0 , "END_SEND_COLUMN_SIZE");

    MPE_Log_event( START_SEND_COLUMN_VALUES, 0 , "START_SEND_COLUMN_VALUES");
#endif
    MPI_Send(column->values, column->size, MPI_DOUBLE, procid, 2, MPI_COMM_WORLD);
#ifdef MPE_LOGS
    MPE_Log_event( END_SEND_COLUMN_VALUES, 0 , "END_SEND_COLUMN_VALUES");

    MPE_Log_event( START_SEND_COLUMN_ID, 0 , "START_SEND_COLUMN_ID");
#endif
    MPI_Send(&column->id, 1, MPI_INT, procid, 3, MPI_COMM_WORLD);
#ifdef MPE_LOGS
    MPE_Log_event( END_SEND_COLUMN_ID, 0 , "END_SEND_COLUMN_ID");
#endif
}

env init(int argc, char** argv) {
    env e;
    MPI_Init(&argc,&argv);
#ifdef MPE_LOGS
    MPE_Init_log();
#endif
    MPI_Comm_size(MPI_COMM_WORLD,&e.numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&e.myid);
    if(e.myid == 0){
      printf("METHOD_MPI type enabled.\n");
#ifdef MPE_LOGS
      printf("MPE_LOGS mode enabled.\n");
      MPE_Describe_state( START_SEND_COLUMN_SIZE,
                          END_SEND_COLUMN_SIZE,
                          "SEND_COLUMN_SIZE", "light blue");
      MPE_Describe_state( START_SEND_COLUMN_VALUES,
                          END_SEND_COLUMN_VALUES,
                          "SEND_COLUMN_VALUES" , "pink" );
      MPE_Describe_state( START_SEND_COLUMN_ID,
                          END_SEND_COLUMN_ID,
                          "SEND_COLUMN_ID" , "green" );
      MPE_Describe_state( START_SEND_DIMENSIONS_ROWS_SIZE,
                          END_SEND_DIMENSIONS_ROWS_SIZE,
                          "SEND_DIMENSIONS_ROWS_SIZE" , "navy" );
      MPE_Describe_state( START_SEND_DIMENSIONS_COLS_SIZE,
                          END_SEND_DIMENSIONS_COLS_SIZE,
                          "SEND_DIMENSIONS_COLS_SIZE" , "yellow" );

      MPE_Describe_state( START_RECV_COLUMN_SIZE,
                          END_RECV_COLUMN_SIZE,
                          "RECV_COLUMN_SIZE" , "blue" );
      MPE_Describe_state( START_RECV_COLUMN_VALUES,
                          END_RECV_COLUMN_VALUES,
                          "RECV_COLUMN_VALUES" , "dark violet" );
      MPE_Describe_state( START_RECV_COLUMN_ID,
                          END_RECV_COLUMN_ID,
                          "RECV_COLUMN_ID" , "dark green" );
      MPE_Describe_state( START_RECV_DIMENSIONS_ROWS_SIZE,
                          END_RECV_DIMENSIONS_ROWS_SIZE,
                          "RECV_DIMENSIONS_ROWS_SIZE" , "dark slate grey" );
      MPE_Describe_state( START_RECV_DIMENSIONS_COLS_SIZE,
                          END_RECV_DIMENSIONS_COLS_SIZE,
                          "RECV_DIMENSIONS_COLS_SIZE" , "dark orange" );
#endif
#ifndef MPE_LOGS
      printf("MPE_LOGS mode disabled.\n");
#endif
    }
    return e;
}

vector* receiveColumn(MPI_Status *status) {
    int size;
    vector* column;

#ifdef MPE_LOGS
    MPE_Log_event( START_RECV_COLUMN_SIZE, 0 , "START_RECV_COLUMN_SIZE");
#endif
    MPI_Recv(&size, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, status);
#ifdef MPE_LOGS
    MPE_Log_event( END_RECV_COLUMN_SIZE, 0 , "END_RECV_COLUMN_SIZE");
#endif
    column = createVector(size);

#ifdef MPE_LOGS
    MPE_Log_event( START_RECV_COLUMN_VALUES, 0 , "START_RECV_COLUMN_VALUES");
#endif
    MPI_Recv(column->values, size, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, status);
#ifdef MPE_LOGS
    MPE_Log_event( END_RECV_COLUMN_VALUES, 0 , "END_RECV_COLUMN_VALUES");

    MPE_Log_event( START_RECV_COLUMN_ID, 0 , "START_RECV_COLUMN_ID");
#endif
    MPI_Recv(&column->id, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, status);
#ifdef MPE_LOGS
    MPE_Log_event( END_RECV_COLUMN_ID, 0 , "END_RECV_COLUMN_ID");
#endif
    return column;
}

int getProcIdByColumn(int column, int numprocs) {
    return column%(numprocs-1)+1;
}

void sendDimensions(int* rows, int* cols, env e) {
    int procid;
    for(procid = 1; procid < e.numprocs; ++procid) {
#ifdef MPE_LOGS
        MPE_Log_event( START_SEND_DIMENSIONS_ROWS_SIZE, 0 ,
                      "START_SEND_DIMENSIONS_ROWS_SIZE");
#endif
        MPI_Send(rows, 1, MPI_INT, procid, 1, MPI_COMM_WORLD);
#ifdef MPE_LOGS
        MPE_Log_event( END_SEND_DIMENSIONS_ROWS_SIZE, 0 ,
                      "END_SEND_DIMENSIONS_ROWS_SIZE");

        MPE_Log_event( START_SEND_DIMENSIONS_COLS_SIZE, 0 ,
                      "START_SEND_DIMENSIONS_COLS_SIZE");
#endif
        MPI_Send(cols, 1, MPI_INT, procid, 2, MPI_COMM_WORLD);
#ifdef MPE_LOGS
        MPE_Log_event( END_SEND_DIMENSIONS_COLS_SIZE, 0 ,
                      "END_SEND_DIMENSIONS_COLS_SIZE");
#endif
    }
}
void receiveDimensions(int* rows, int* cols) {
    MPI_Status status;
#ifdef MPE_LOGS
    MPE_Log_event( START_RECV_DIMENSIONS_ROWS_SIZE, 0 ,
                  "START_RECV_DIMENSIONS_ROWS_SIZE");
#endif
    MPI_Recv(rows, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
#ifdef MPE_LOGS
    MPE_Log_event( END_RECV_DIMENSIONS_ROWS_SIZE, 0 ,
                  "END_RECV_DIMENSIONS_ROWS_SIZE");

    MPE_Log_event( START_RECV_DIMENSIONS_COLS_SIZE, 0 ,
                  "START_RECV_DIMENSIONS_COLS_SIZE");
#endif
    MPI_Recv(cols, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
#ifdef MPE_LOGS
    MPE_Log_event( END_RECV_DIMENSIONS_COLS_SIZE, 0 ,
                  "END_RECV_DIMENSIONS_COLS_SIZE");
#endif
}

matrix* decompose(matrix* m, env e) {
    int n, procit;
    int j,k,s;
    vector *column, *kcolumn, *recvKcolumn, *recvColumn;
    matrix *buffer;
    int bufferPos;
    MPI_Status status;
    int cols = m->cols;
    int myid = e.myid, numprocs = e.numprocs;
    if (myid != 0) {
        buffer = createMatrix(m->rows, cols/(numprocs-1)+1);
    }
    for(k=1; k <= cols-1; k++){
        if (myid == 0) {
            // STEP 1
            for (s=k+1; s <= m->rows; s++) {
                setMatValue(m, s, k, getMatValue(m, s, k)/getMatValue(m, k, k));
            }
            kcolumn = getColumn(m, k);
            for (procit = 1; procit < numprocs; ++procit) {
                sendColumn(kcolumn, procit);
            }
            freeVector(kcolumn);
        } else {
            recvKcolumn = receiveColumn(&status);
        }
        // STEP 2
        j = k + 1;
        if (myid == 0) {
            int procid;
            int columns2work = cols - k;
            int counter = 0;
            while(j <= cols) {
                for(procid = 1; procid < numprocs; ++procid) {
                    if (j <= cols) {++counter;
                        column = getColumn(m, j);
                        sendColumn(column, procid);
                        freeVector(column);
                    }
                    ++j;
                }
            }
            j = 0;
            while(j < columns2work) {
                column = receiveColumn(&status);
                setColumn(m, column, column->id);
                freeVector(column);
                ++j;
            }
        } else {
            bufferPos = 1;
            for(j = k+myid; j <= cols; j = j + numprocs-1) {
                recvColumn = receiveColumn(&status);
                setColumn(buffer, recvColumn, bufferPos);
                freeVector(recvColumn);
                ++bufferPos;
            }
            bufferPos = 1;
            for(j = k+myid; j <= cols; j = j + numprocs-1) {
                recvColumn = getColumn(buffer, bufferPos);
                updateColumn(recvColumn, recvKcolumn, recvKcolumn->id);
                sendColumn(recvColumn, 0);
                freeVector(recvColumn);
                ++bufferPos;
            }
        }
        if (myid != 0) {
            freeVector(recvKcolumn);
        }
    }
    if (myid != 0) {
        freeMatrix(buffer);
    }
    return m;
}

void finish() {
#ifdef MPE_LOGS
    MPE_Finish_log("bin/mpe_logs");
#endif
    MPI_Finalize();
}

#endif
