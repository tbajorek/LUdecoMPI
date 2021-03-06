/*
 * File:   vector.h
 * Author: tomek
 *
 * Created on 5 kwietnia 2017, 04:11
 */

#ifndef VECTOR_H
#define	VECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef double cell;

    typedef struct {
        cell* values;
        int size;
        int id;
    } vector;

    vector* createVector(int size);
    vector* zeroVector(int size);
    vector* createFromArray(cell* values, int size);
    void freeVector(vector* v);
    void setVecValue(vector* v, int pos, cell value);
    double getVecValue(vector* v, int pos);
    void displayVector(vector* v);
    vector* readVectorFromFile(const char* filename);
    void writeVectorToFile(const char* filename, vector* v);


#ifdef	__cplusplus
}
#endif

#endif	/* VECTOR_H */
