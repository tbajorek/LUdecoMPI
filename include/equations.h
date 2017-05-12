#ifndef EQUATIONS_H
#define	EQUATIONS_H

    #include "LU.h"
    
    /**
     * Structure represents a system of linear equations
     */
    typedef struct {
        /**
         * Coefficient matrix
         */
        matrix* A;
        /**
         * Solution vector
         */
        vector* x;
        /**
         * Constant terms vector
         */
        vector* b;
    } equations;
    
    /**
     * Make free the occupied memory of the equation system
     * @param eq
     */
    void freeEquations(equations* eq);
    
    /**
     * Solve the passed equation system. Solved system is located inside the equation variable.
     * @param eq The passed equation system
     * @param e Environment variable
     */
    void solve(equations* eq, env e);

#endif	/* EQUATIONS_H */