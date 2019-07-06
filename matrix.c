#include <stdio.h>

typedef struct matrix_s
{
  unsigned int nrows, ncols;
  double *data;
} matrix;			// size: 16 bytes

#define mx_get(m, r, c) ((m).data[(r)*(m).ncols + (c)])
#define mx_set(m, r, c, v) ((m).data[(r)*(m).ncols + (c)] = v)

int
mx_eq (matrix left, matrix right)
{
  if (left.nrows != right.nrows)
    return 0;
  if (left.ncols != right.ncols)
    return 0;

  for (int i = 0; i < (left.nrows * left.ncols); i++)
    {
      if (left.data[i] != right.data[i])
	return 0;
    }
  return 1;
}

void
mx_print (matrix m)
{
  printf ("matrix (%d rows x %d columns):\n", m.nrows, m.ncols);
  for (int i = 0; i < m.nrows; i++)
    {
      for (int j = 0; j < m.ncols; j++)
	{
	  printf ("%.2f", mx_get (m, i, j));
	  if ((j + 1) < m.ncols)
	    printf ("\t");
	}
      printf ("\n");
    }
}

#ifdef TEST_matrix
int
main ()
{
  setbuf (stdout, NULL);

  double d[] = { 5.0, 4.0, 3.0,
    8.0, 1.0, 6.0
  };
  matrix m = {
    .nrows = 2,.ncols = 3,
    .data = d
  };

  mx_print (m);
}
#endif
