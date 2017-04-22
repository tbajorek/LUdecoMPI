#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/matrix.h"

matrix* createMatrix(int rows, int cols) {
    matrix* m;
    int j;
    m = (matrix*) malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->values = (cell**) malloc(cols*sizeof(cell*));
    for (j = 0; j < m->cols; ++j) {
        m->values[j] = (cell*) malloc(rows*sizeof(cell));
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

matrix* copyMatrix(matrix * m) {
    int i, j;
    matrix* m2 = zeroMatrix(m->rows, m->cols);
    for(i = 1; i <= m->rows; ++i) {
        for (j = 1; j <= m->cols; ++j) {
            setMatValue(m2, i, j, getMatValue(m, i, j));
        }
    }
    return m2;
}

matrix* createMatrixFromArray(const double** a, int rows, int cols) {
    int i, j;
    matrix* m = createMatrix(rows, cols);
    for(i = 1; i < rows; ++i) {
        for(j = 1; j < rows; ++j) {
            setMatValue(m, i, j, a[i-1][j-1]);
        }
    }
    return m;
}

double getMatValue(matrix* m, int row, int col) {
    return m->values[col-1][row-1];
}

void setMatValue(matrix* m, int row, int col, cell value) {
    m->values[col-1][row-1] = value;
}

void displayMatrix(matrix* m) {
    int i, j;
    cell value;
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

vector* getColumn(matrix* m, int column) {
    vector* v = createVector(m->cols);
    memcpy((void*)v->values, (const void*)m->values[column-1], (size_t)(m->cols*sizeof(cell)));
    return v;
}

void setColumn(matrix* m, vector* c, int column) {
    memcpy((void*)m->values[column-1], (const void*)c->values, (size_t)(c->size*sizeof(cell)));
}

matrix* readFromFile(const char* filename) {
    int rows, cols, i, j;
    cell buffer;
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
    cell value;
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
