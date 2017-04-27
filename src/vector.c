#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vector.h"

vector* createVector(int size) {
    vector* v = (vector*)malloc(sizeof(vector));
    v->values = (cell*)calloc(size,sizeof(cell));
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

vector* ghostVector(int rows) {
    vector* v;
    v = (vector*) malloc(sizeof(vector));
    v->size = rows;
    v->values = 0;
    return v;
}

void displayVector(vector* v){
    int i, j;
    double value;
    for (i = 0; i < v->size; ++i) {
        value = v->values[i];
        printf("%lf\t", value);
    }
    printf("\n");
}

vector* createFromArray(cell* values, int size) {
    vector* v = createVector(size);
    memcpy(values, v->values, sizeof(values));
    return v;
}

void freeVector(vector* v) {
    if (v->values != 0) {
        free(v->values);
    }
    free(v);
}

void setVecValue(vector* v, int pos, double value) {
    v->values[pos-1] = value;
}

double getVecValue(vector* v, int pos) {
    return v->values[pos-1];
}

vector* readVectorFromFile(const char* filename) {
    int rows, i;
    cell buffer;
    vector* v;
    FILE *mfile = fopen(filename, "r");
    fscanf(mfile, "%d\n", &rows);
    v = createVector(rows);
    for(i = 1; i <= v->size; ++i) {
        fscanf(mfile, "%lf\n", &buffer);
        setVecValue(v, i, buffer);
    }
    fclose(mfile);
    return v;
}

void writeVectorToFile(const char* filename, vector* v) {
    int i, j;
    cell value;
    FILE *vfile = fopen(filename, "w+");
    fprintf(vfile, "%d\n", v->size);
    for(i = 1; i <= v->size; ++i) {
        value = getVecValue(v, i);
        fprintf(vfile, "%lf\n", value);
    }
    fclose(vfile);
}