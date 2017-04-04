/* 
 * File:   maina.c
 * Author: tomek
 *
 * Created on 4 kwietnia 2017, 03:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "include/matrix.h"

/*
 * 
 */
int main(int argc, char** argv) {
    double x;
    matrix* m = zeroMatrix(12,12);
    setValue(m,5,6,10);
    x = getValue(m,5,6);
    printf("%f\n", x);
    displayMatrix(m);
    freeMatrix(m);
    return (EXIT_SUCCESS);
}

