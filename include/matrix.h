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

    #include "vector.h"

    typedef struct {
        double **values;
        int rows;
        int cols;
    } matrix;

    matrix* createMatrix(int rows, int cols);
    matrix* zeroMatrix(int rows, int cols);
    matrix* copyMatrix(matrix * m);
    double getMatValue(matrix* m, int row, int cols);
    void setMatValue(matrix* m, int row, int cols, double value);
    void displayMatrix(matrix* m);
    void freeMatrix(matrix* m);
    vector* getColumn(matrix* m, int column);
    vector* getRow(matrix* m, int row);
    matrix* readFromFile(const char* filename);
    void writeToFile(const char* filename, matrix* m);


#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */
