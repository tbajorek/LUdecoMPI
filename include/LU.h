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
    
    #define METHOD_MPI

    matrix* decompose(matrix* m, int argc, char** argv);

#ifdef	__cplusplus
}
#endif

#endif	/* LU_H */
