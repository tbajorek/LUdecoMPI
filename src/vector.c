#include <stdlib.h>
#include <string.h>
#include "../include/vector.h"

vector* createVector(int size) {
    vector* v = (vector*)malloc(sizeof(vector));
    v->values = (double*)calloc(size,sizeof(double));
    v->size = size;
    return v;
}

vector* createFromArray(double* values, int size) {
    vector* v = createVector(size);
    memcpy(values, v->values, sizeof(values));
    return v;
}

void freeFector(vector* v) {
    free(v->values);
    free(v);
}

void setVecValue(vector* v, int pos, double value) {
    v->values[pos-1] = value;
}

double getVecValue(vector* v, int pos) {
    return v->values[pos-1];
}
