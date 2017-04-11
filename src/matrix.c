#include <stdlib.h>
#include <stdio.h>

#include "../include/matrix.h"

matrix* createMatrix(int rows, int cols) {
    matrix* m;
    int j;
    m = (matrix*) malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->values = (double**) malloc(cols*sizeof(double*));
    for (j = 0; j < m->cols; ++j) {
        m->values[j] = (double*) malloc(rows*sizeof(double));
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

double getMatValue(matrix* m, int row, int col) {
    return m->values[col-1][row-1];
}

void setMatValue(matrix* m, int row, int col, double value) {
    m->values[col-1][row-1] = value;
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
    for (i = 0; i < m->cols; ++i) {
        free(m->values[i]);
    }
    free(m->values);
    free(m);
}

vector* getRow(matrix* m, int row) {
    vector* v = createVector(m->rows);
    int i;
    for(i = 1; i <= m->cols; ++i) {
        setVecValue(v, i, getMatValue(m, row, i));
    }
    return v;
}

vector* getColumn(matrix* m, int col) {
    vector* v = createVector(m->cols);
    memcpy(m->values[col-1], v->values, sizeof(m->values[col-1]));
    return v;
}

matrix* readFromFile(const char* filename) {
    int rows, cols, i, j;
    double buffer;
    matrix* m;
    FILE *mfile = fopen(filename, "r");
    fscanf(mfile, "%d\t%d\n", &rows, &cols);
    m = createMatrix(rows, cols);
    for(i = 1; i <= m->rows; ++i) {
        for (j = 1; j <= m->cols; ++j) {
            fscanf(mfile, "%lf\t", &buffer);
            setMatValue(m, i, j, buffer);
        }
        fscanf(mfile, "\n");
    }
    fclose(mfile);
    return m;
}

void writeToFile(const char* filename, matrix* m) {
    int i, j;
    double value;
    FILE *mfile = fopen(filename, "w+");
    fprintf(mfile, "%d\t%d\n", m->rows, m->cols);
    for(i = 1; i <= m->rows; ++i) {
        for (j = 1; j <= m->cols; ++j) {
            value = getMatValue(m, i, j);
            fprintf(mfile, "%lf\t", value);
        }
        fprintf(mfile, "\n");
    }
    fclose(mfile);
}
