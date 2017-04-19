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

    matrix* decompose(matrix* m);

    //double compute_l_ij(int rowi, int colj, matrix * matrix_obj);


#ifdef	__cplusplus
}
#endif

#endif	/* LU_H */
