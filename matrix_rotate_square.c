#include <assert.h>
#include "matrix.c"

void rotate(matrix img){
    int n = img.nrows-1; // maximum index

    int sc = 0; // start column for element rotation
    int ec = n; // end column for element rotation (exclusive of)
    int i = 0;  // current row

    // We rotate in place (see below)
    // at positions marker as "o".
    // Positions marked as "x" are filled in
    // by the rotations, and as such we don't need
    // to start rotating from them.
    // o o o x
    // x o x x
    // x x x x
    // x x x x
    while(sc <= ec){
        for(int j=sc; j<ec; j++){ // rotate all needed cols in current row
            //  we rotate in place four corners
            //  starting at a "starting" position (i, j)
            //  0  ==> 1
            //  /\     ||
            //  ||     \/
            //  3  <== 2
            int p0 = mx_get(img, i, j);
            int p1 = mx_get(img, j, n-i);
            int p2 = mx_get(img, n-i, n-j);
            int p3 = mx_get(img, n-j, i);

            mx_set(img, j, n-i, p0);
            mx_set(img, n-i, n-j, p1);
            mx_set(img, n-j, i, p2);
            mx_set(img, i, j, p3);
        }
        sc++; // skip one col left after rotating all columns in current row
        ec--; // skip one col right after rotating all columns in current row
        i++;  // go to the next row
    }
}

#ifdef TEST_matrix_rotate_square
int main(){
    setbuf(stdout, NULL);

    double d[] = {4.0, 2.0, 5.0, 3.0, 1.0,
                  8.0, 1.0, 6.0, 1.0, 0.0,
                  2.0, 4.0, 8.0, 3.0, 2.0,
                  7.0, 4.0, 2.0, 0.0, 3.0,
                  0.0, 2.0, 1.0, 9.0, 11.0};
    matrix img = {
      .nrows = 5, .ncols = 5,
      .data = d
    };

    double r[] = { 0.0, 7.0, 2.0, 8.0, 4.0,
                   2.0, 4.0, 4.0, 1.0, 2.0,
                   1.0, 2.0, 8.0, 6.0, 5.0,
                   9.0, 0.0, 3.0, 1.0, 3.0,
                   11.0, 3.0, 2.0, 0.0, 1.0 };
    matrix rimg = {
        .nrows = 5, .ncols = 5,
        .data = r
    };

    printf("Matrix rotation test:\n");
    printf("Original:\n");
    mx_print(img);

    rotate(img);

    printf("Rotated:\n");
    mx_print(img);

    printf("Expected rotation:\n");
    mx_print(rimg);

    assert(mx_eq(img, rimg));

    printf("They seem equal.\n");
}
#endif
