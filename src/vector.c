#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vector.h"

vector* createVector(int size) {
    vector* v = (vector*)malloc(sizeof(vector));
    v->values = (double*)calloc(size,sizeof(double));
    v->size = size;
    return v;
}

vector* zeroVector(int size) {
    vector* m;
    int i, j;
    m = createVector(size);
    for(i = 0; i < m->size; ++i) {
      m->values[i] = 0;
    }
    return m;
}

void displayVector(vector* v){
    printf("-------vector begin-------\n");
    int i, j;
    double value;
    for (i = 0; i < v->size; ++i) {
        value = v->values[i];
        printf("%lf\t", value);
    }
    printf("\n");
    printf("-------vector end-------\n");
}

vector* createFromArray(double* values, int size) {
    vector* v = createVector(size);
    memcpy(values, v->values, sizeof(values));
    return v;
}

void freeVector(vector* v) {
    free(v->values);
    free(v);
}

void setVecValue(vector* v, int pos, double value) {
    v->values[pos-1] = value;
}

double getVecValue(vector* v, int pos) {
    return v->values[pos-1];
}
