#ifndef LU_H
#define	LU_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "matrix.h"
    
    /**
     * Structure represents an environment where the matrix is deccomposed
     */
    typedef struct {
        /**
         * Identificator of processor where is working the application
         */
        int myid;
        /**
         * Total number of all used processors
         */
        int numprocs;
    } env;

    /**
     * Initialize computing of LU matrixes. Environment variable is returned.
     * @param argc Number of parameters passed to the program
     * @param argv List of passed parameters
     * @return 
     */
    env init(int argc, char** argv);
    
    /**
     * Send dimensions of computed matrix
     * @param rows Number of rows
     * @param cols Number of columns
     * @param e Environment variable
     */
    void sendDimensions(int* rows, int* cols, env e);
    
    /**
     * Receive dimensions of computed matrix
     * @param rows Number of rows
     * @param cols Number of columns
     */
    void receiveDimensions(int* rows, int* cols);
    
    /**
     * Decompose the passed matrix using the given environment
     * @param m The given matrix to decompose
     * @param e Environment variable
     * @return 
     */
    matrix* decompose(matrix* m, env e);
    
    /**
     * Finish remained things after computing
     */
    void finish();

#ifdef	__cplusplus
}
#endif

#endif	/* LU_H */
