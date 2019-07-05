#include "matrix.h"

int main(){
    setbuf(stdout, NULL);

    double d[] = {5.0, 4.0, 3.0,
                  8.0, 1.0, 6.0};
    matrix m = {
      .nrows = 2, .ncols = 3,
      .data = d
    };

    mx_print(m);
}
