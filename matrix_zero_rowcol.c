#include <assert.h>
#include <string.h>
#include "common/matrix.h"

void zero_rowcol(matrix m)
{
    int zero_rows[m.nrows];
    int zero_cols[m.ncols];

    memset(zero_rows, 0, m.nrows * sizeof(int));
    memset(zero_cols, 0, m.ncols * sizeof(int));

    for (int i = 0; i < m.nrows; i++) {
        for (int j = 0; j < m.ncols; j++) {
            if (mx_get(m, i, j) == 0.0) {
                zero_rows[i] = 1;
                zero_cols[j] = 1;
            }
        }
    }

    // TODO: what if the first row is all zeros?
    // how to skip the rest of the mattrix?
    // do I care?

    for (int i = 0; i < m.nrows; i++) {
        for (int j = 0; j < m.ncols; j++) {
            if (zero_rows[i] || zero_cols[j]) {
                mx_set(m, i, j, 0.0);
            }
        }
    }

}

#ifdef TEST_matrix_zero_rowcol
int main()
{
    setbuf(stdout, NULL);

    double m_data[] = {
        4.0, 2.0, 5.0, 3.0, 1.0,
        8.0, 1.0, 6.0, 1.0, 0.0,
        2.0, 4.0, 8.0, 3.0, 2.0,
        7.0, 4.0, 2.0, 0.0, 3.0,
        0.0, 2.0, 1.0, 9.0, 1.0
    };
    matrix m = {
        .nrows = 5,.ncols = 5,
        .data = m_data
    };

    double e_data[] = {
        0.0, 2.0, 5.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 4.0, 8.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0
    };
    matrix e = {
        .nrows = 5,.ncols = 5,
        .data = e_data
    };

    printf("The matrix to zero rows and columns for:\n");
    mx_print(m);

    printf("The expected result:\n");
    mx_print(e);

    printf("The actual result:\n");
    zero_rowcol(m);
    mx_print(m);

    assert(mx_eq(m, e));
    printf("Looks like they are equal.\n");
}
#endif
