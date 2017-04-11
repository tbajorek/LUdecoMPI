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

    typedef struct {
        double* values;
        int size;
    } vector;

    vector* createVector(int size);
    vector* createFromArray(double* values, int size);
    void freeFector(vector* v);
    void setVecValue(vector* v, int pos, double value);
    double getVecValue(vector* v, int pos);


#ifdef	__cplusplus
}
#endif

#endif	/* VECTOR_H */
