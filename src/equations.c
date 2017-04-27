#include "../include/equations.h"

void solve(equations* eq, env e) {
    eq->A = decompose(eq->A, e);
    //STEP 1
    
    //STEP 2
    
}

void freeEquations(equations* eq) {
    freeMatrix(eq->A);
    freeVector(eq->x);
    freeVector(eq->b);
}