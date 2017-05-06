/*
 * File:   LU.h
 * Author: tomek
 *
 * Created on 11 kwietnia 2017, 19:12
 */

#ifndef LU_H
#define	LU_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "matrix.h"

    typedef struct {
        matrix* m;
        int pid;
    } result;

    typedef struct {
        int myid;
        int numprocs;
    } env;

    env init(int argc, char** argv);
    void sendDimensions(int* rows, int* cols, env e);
    void receiveDimensions(int* rows, int* cols);
    matrix* decompose(matrix* m, env e);
    void finish();

#ifdef	__cplusplus
}
#endif

#endif	/* LU_H */
