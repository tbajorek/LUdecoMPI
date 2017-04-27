/*
 * File:   maina.c
 * Author: tomek
 *
 * Created on 4 kwietnia 2017, 03:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/equations.h"

int main(int argc, char** argv) {
    clock_t endTime, beginTime = clock();
    int rows, cols;
    matrix *m, *m2;
    vector* x, b;
    equations eq;
    env e = init(argc, argv);
    if (e.myid == 0) {
        eq.A = readMatrixFromFile("data/A.txt");
        //eq.b = readVectorFromFile("data/b.txt");
        rows = m->rows;
        cols = m->cols;
        sendDimensions(&m->rows, &m->cols, e);
    } else {
        receiveDimensions(&rows, &cols);
        eq.A = ghostMatrix(rows, cols);
        eq.b = ghostVector(rows);
    }
    solve(&eq, e);
    
    if (e.myid == 0) {
        writeMatrixToFile("data/LU.txt", eq.A);
        //writeVectorToFile("data/x.txt", eq.x);
    }
    //freeEquations(&eq);
    endTime = clock();
    if (e.myid == 0) {
        printf("Wymiary macierzy: %d x %d\n", rows, cols);
        printf("Ilosc procesow: %d\n", e.numprocs);
        printf("Czas wykonania: %lf\n", (double)(endTime - beginTime) / CLOCKS_PER_SEC);
    }
    finish();
    return (EXIT_SUCCESS);
}

/**
 LU:
 3.000000	4.000000	7.000000	8.000000	1.000000	6.000000	
 0.666667	2.333333	3.333333	-4.333333	4.333333	5.000000	
 1.000000	0.857143	-0.857143	2.714286	3.285714	-1.285714	
 1.666667	-1.142857	5.666667	-24.666667	-10.333333	11.000000	
 1.000000	2.142857	15.333333	1.310811		-42.121622	-7.418919	
 1.333333	-1.428571	-4.000000	0.081081		-0.613410	-6.442733	
 */
