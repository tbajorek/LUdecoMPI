#ifndef MATRIX_H
#define	MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include "vector.h"
    
    /**
     * Structure represents a matrix
     */
    typedef struct {
        /**
         * 2-dimensional array with values
         */
        cell **values;
        /**
         * Number of rows
         */
        int rows;
        /**
         * Number of columns
         */
        int cols;
    } matrix;
    
    /**
     * Create an empty matrix with passed size without initialization. Created matrix is returned.
     * @param rows Number of rows
     * @param cols Number of columns
     * @return 
     */
    matrix* createMatrix(int rows, int cols);
    
    /**
     * Create a matrix with passed size. Elements are initialized as 0. Created matrix is returned.
     * @param rows Number of rows
     * @param cols Number of columns
     * @return 
     */
    matrix* zeroMatrix(int rows, int cols);
    
    /**
     * Create a "ghost" matrix with passed size. A memory for values isn't allocated. Created matrix is returned.
     * @param rows Number of rows
     * @param cols Number of columns
     * @return 
     */
    matrix* ghostMatrix(int rows, int cols);
    
    /**
     * Create a copy of passed matrix. The copy is returned.
     * @param m The original matrix
     * @return 
     */
    matrix* copyMatrix(matrix * m);
    
    /**
     * Create a matrix from double pointer with double values. It uses passed size. Created matrix is returned.
     * @param a Array with values
     * @param rows Number of rows
     * @param cols Number of columns
     * @return 
     */
    matrix* createMatrixFromArray(const double** a, int rows, int cols);
    
    /**
     * Return a value of passed matrix from the given position
     * @param m Passed matrix
     * @param row Requested row number
     * @param col Requested column number 
     * @return 
     */
    double getMatValue(matrix* m, int row, int col);
    
    /**
     * Set the given value to the passed position in matrix
     * @param m Passed matrix
     * @param row Row number
     * @param col Column number
     * @param value The given value
     */
    void setMatValue(matrix* m, int row, int col, cell value);
    
    /**
     * Display the given matrix in a console
     * @param m The passed matrix
     */
    void displayMatrix(matrix* m);
    
    /**
     * Make an occupied memory free. It prevents memory leaks.
     * @param m The passed matrix
     */
    void freeMatrix(matrix* m);
    
    /**
     * Return a copy of matrix column from the given position. It creates a new entity which can make free separately after using the value.
     * @param m The passed matrix
     * @param column Column number
     * @return 
     */
    vector* getColumn(matrix* m, int column);
    
    /**
     * Set the passed column to the matrix on the given position
     * @param m The passed matrix
     * @param c Vector with matrix column
     * @param column Number of column
     */
    void setColumn(matrix* m, vector* c, int column);
    
    /**
     * Return a copy of matrix column from the given position. It creates a new entity which can make free separately after using the value.
     * @param m The passed matrix
     * @param row Number of row
     * @return 
     */
    vector* getRow(matrix* m, int row);
    
    /**
     * Read a matrix from file with the passed filename. Read matrix is returned.
     * @param filename Name of file
     * @return 
     */
    matrix* readMatrixFromFile(const char* filename);
    
    /**
     * Write the passed matrix to a file with the passed filename
     * @param filename Name of file
     * @param m
     */
    void writeMatrixToFile(const char* filename, matrix* m);


#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

