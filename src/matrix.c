#include <stdlib.h>
#include <stdio.h>

#include "include/matrix.h"

matrix* createMatrix(int rows, int cols) {
    matrix* m;
    int i;
    m = (matrix*) malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->values = (double**) malloc(rows*sizeof(double*));
    for (i = 0; i < m->rows; ++i) {
        m->values[i] = (double*) malloc(cols*sizeof(double));
    }
    return m;
}

matrix* zeroMatrix(int rows, int cols) {
    matrix* m;
    int i, j;
    m = createMatrix(rows, cols);
    for(i = 1; i <= m->rows; ++i) {
        for (j = 1; j <= m->cols; ++j) {
            setMatValue(m, i, j, 0);
        }
    }
    return m;
}

double getMatValue(matrix* m, int row, int cols) {
    return m->values[row-1][cols-1];
}

void setMatValue(matrix* m, int row, int cols, double value) {
    m->values[row-1][cols-1] = value;
}

void displayMatrix(matrix* m) {
    int i, j;
    double value;
    for(i = 1; i <= m->rows; ++i) {
        for (j = 1; j <= m->cols; ++j) {
            value = getMatValue(m, i, j);
            printf("%f\t", value);
        }
        printf("\n");
    }
}

void freeMatrix(matrix* m) {
    int i;
    for (i = 0; i < m->rows; ++i) {
        free(m->values[i]);
    }
    free(m->values);
    free(m);
}

vector* getColumn(matrix* m, int column) {
    vector* v = createVector(m->rows);
    int i;
    for(i = 1; i <= m->rows; ++i) {
        setVecValue(v, i, getMatValue(m, i, column));
    }
    return v;
}

vector* getRow(matrix* m, int row) {
    vector* v = createVector(m->cols);
    memcpy(m->values[row-1], v->values, sizeof(m->values[row-1]));
    return v;
}