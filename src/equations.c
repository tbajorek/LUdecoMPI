#include "../include/equations.h"

double calculateLsum(equations* eq, int i) {
    int j;
    int sum = 0.0;
    for(j = 1; j < i; ++i) {
        sum += getMatValue(eq->A, i, j)*getVecValue(eq->x, j);
    }
    return sum;
}

double calculateRsum(equations* eq, int i) {
    int j;
    int sum = 0.0;
    for(j = i + 1; j <= eq->x->size; ++i) {
        sum += getMatValue(eq->A, i, j)*getVecValue(eq->x, j);
    }
    return sum;
}

void solve(equations* eq, env e) {
    int i;
    eq->A = decompose(eq->A, e);
    eq->x = createVector(eq->b->size);
    //STEP 1 - calculating y
    setVecValue(eq->x, 1, getVecValue(eq->b, 1));//first value of Y
    for (i = 2; i < eq->x->size; ++i) {//for next n values of Y
        setVecValue(eq->x, i, getVecValue(eq->b, i) - calculateLsum(eq, i));
    }
    //STEP 2
    setVecValue(eq->x, eq->x->size, getVecValue(eq->x, eq->x->size)/getMatValue(eq->A, eq->x->size, eq->x->size));//last value of X
    for (i = eq->x->size - 1; i > 0; --i) {//every next value of X
        setVecValue(eq->x, i, (getVecValue(eq->x, i) - calculateRsum(eq, i))/getMatValue(eq->A, i, i));
    }
}

void freeEquations(equations* eq) {
    freeMatrix(eq->A);
    freeVector(eq->x);
    freeVector(eq->b);
}