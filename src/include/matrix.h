/* 
 * File:   matrix.h
 * Author: tomek
 *
 * Created on 4 kwietnia 2017, 03:38
 */

#ifndef MATRIX_H
#define	MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct matrix {
        double **values;
        int rows;
        int cols;
    } matrix;
    
    matrix* createMatrix(int rows, int cols);
    matrix* zeroMatrix(int rows, int cols);
    double getValue(matrix* m, int row, int cols);
    void setValue(matrix* m, int row, int cols, double value);
    void displayMatrix(matrix* m);
    void freeMatrix(matrix* m);
    double* getCols(matrix* m);
    double* getRows(matrix* m);


#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

