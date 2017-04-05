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
    matrix* m = zeroMatrix(12,12);
    setMatValue(m,5,6,10);
    displayMatrix(m);
    freeMatrix(m);
    return (EXIT_SUCCESS);
}

