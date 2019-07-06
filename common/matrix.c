#include <stdio.h>
#include "matrix.h"

int mx_eq(matrix left, matrix right)
{
    if (left.nrows != right.nrows)
	return 0;
    if (left.ncols != right.ncols)
	return 0;

    for (int i = 0; i < (left.nrows * left.ncols); i++) {
	if (left.data[i] != right.data[i])
	    return 0;
    }
    return 1;
}

void mx_print(matrix m)
{
    printf("matrix (%d rows x %d columns):\n", m.nrows, m.ncols);
    for (int i = 0; i < m.nrows; i++) {
	for (int j = 0; j < m.ncols; j++) {
	    printf("%.2f", mx_get(m, i, j));
	    if ((j + 1) < m.ncols)
		printf("\t");
	}
	printf("\n");
    }
}
