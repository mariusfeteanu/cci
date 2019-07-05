#include <stdio.h>

typedef struct matrix_s {
  unsigned int nrows, ncols;
  double *data;
} matrix; // size: 16 bytes

#define mx_get(m, r, c) ((m).data[(r)*(m).ncols + (c)])
#define mx_set(m, r, c, v) ((m).data[(r)*(m).ncols + (c)] = v)

void mx_print(matrix m){
  printf("matrix (%d rows x %d columns):\n", m.nrows, m.ncols);
  for(int i = 0; i < m.nrows; i++){
    for(int j = 0; j < m.ncols; j++){
      printf("%f", mx_get(m, i, j));
      if((j + 1) < m.ncols) printf("\t");
    }
    printf("\n");
  }
}
