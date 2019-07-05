#include "matrix.h"

void rotate(matrix img){
    int n=img.nrows-1;

    int sc = 0;
    int ec = img.nrows-2;
    int i = 0;

    while(sc <= ec){
        for(int j=sc; j<=ec; j++){
            printf("%d %d\n", i, j);

            int p1, p2;

            p1 = mx_get(img, j, n-i);
            mx_set(img, j, n-i, mx_get(img, i, j));

            p2 = mx_get(img, n-i, n-j);
            mx_set(img, n-i, n-j, p1);

            p1 = mx_get(img, n-j, i);
            mx_set(img, n-j, i, p2);

            mx_set(img, i, j, p1);
        }
        sc++;
        ec--;
        i++;
    }
}

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

    mx_print(img);

    rotate(img);

    mx_print(img);
}
