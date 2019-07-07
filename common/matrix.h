#pragma once
#include <stdio.h>

typedef struct matrix_s {
    unsigned int nrows, ncols;
    double *data;
} matrix;                       // size: 16 bytes

#define mx_get(m, r, c) ((m).data[(r)*(m).ncols + (c)])
#define mx_set(m, r, c, v) ((m).data[(r)*(m).ncols + (c)] = v)

int mx_eq(matrix left, matrix right);

void mx_print(matrix m);
