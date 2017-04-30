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
    char* afile, *bfile, *xfile;
    int rows = 123654, cols;
    matrix *m, *m2;
    vector* x, b;
    equations eq;
    env e = init(argc, argv);
    if (e.myid == 0) {
        if (argc < 4) {
            printf("Program is running with default parameters.\n");
            afile = "data/A.txt";
            bfile = "data/b.txt";
            xfile = "data/x.txt";
        } else {
            afile = (char*)argv[1];
            bfile = (char*)argv[2];
            xfile = (char*)argv[3];
        }
        eq.A = readMatrixFromFile((const char*)afile);
        eq.b = readVectorFromFile((const char*)bfile);
        eq.x = 0;
        rows = eq.A->rows;
        cols = eq.A->cols;
        sendDimensions(&eq.A->rows, &eq.A->cols, e);
    } else {
        receiveDimensions(&rows, &cols);
        eq.A = ghostMatrix(rows, cols);
        eq.b = ghostVector(rows);
        eq.x = 0;
    }
    solve(&eq, e);
    
    if (e.myid == 0) {
        writeMatrixToFile("data/LU.txt", eq.A);
        writeVectorToFile((const char*)xfile, eq.x);
    }
    freeEquations(&eq);
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
