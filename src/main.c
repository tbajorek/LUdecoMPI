/*
 * File:   maina.c
 * Author: tomek
 *
 * Created on 4 kwietnia 2017, 03:37
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

/*
 *
 */
int main(int argc, char** argv) {
    matrix* m2;
    matrix* m = zeroMatrix(3,3);
    setMatValue(m,1,1,10);
    setMatValue(m,2,3,4);
    setMatValue(m,3,2,7);
    //displayMatrix(m);
    writeToFile("bin/test.txt", m);
    m2 = readFromFile("bin/test.txt");
    displayMatrix(m2);
    freeMatrix(m2);
    freeMatrix(m);
    return (EXIT_SUCCESS);
}
