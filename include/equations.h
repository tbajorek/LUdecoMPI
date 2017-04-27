/* 
 * File:   equations.h
 * Author: tomek
 *
 * Created on 27 kwietnia 2017, 15:25
 */

#ifndef EQUATIONS_H
#define	EQUATIONS_H

#include "LU.h"

typedef struct {
    matrix* A;
    vector* x;
    vector* b;
} equations;

void freeEquations(equations* eq);
void solve(equations* eq, env e);

#endif	/* EQUATIONS_H */

