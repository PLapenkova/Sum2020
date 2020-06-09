/* Lapenkova Polina */
/* FILE NAME: T05DET.C
 * PROGRAMMER: PL5
 * DATE: 03.06.2020
 * PURPOSE: Matrix determinate searching
 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 10

/* Base float point type */
typedef DOUBLE DBL;

/* Matrix size */
INT N;

/* Work matrix */
DBL A[MAX][MAX];

/* Result matrix determinant */
DBL Determinant;

/* Permutation table */
INT P[MAX];

/* Parity flag */
BOOL Parity;

/* Function that loads matrix from file.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;

  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Read size */
  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;

  /* Read matrix data */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
} /* End of 'LoadMatrix' function */

/* Save reult function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID Save( VOID )
{ 
  INT i, j;

  FILE *F = fopen("m3.TXT", "a");
 
  if (F != NULL)
  {
    fprintf(F, "Size: %d\n", N);
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < N; j++)
        fprintf(F, "%10.3f ", A[i][j]);
      fprintf(F, "\n");
    }
    fprintf(F, "Solution: %f\n", Determinant);
    fclose(F);
  }
}
/* End of 'Save' function */ 

/* Swaps two elements function.
 * ARGUMENTS:
 *   - elements which are swapped:
 *     INT X, Y;
 * RETURNS: None.
 */
VOID Swap( INT *X, INT *Y )
{
  INT tmp = *X;

  *X = *Y;
  *Y = tmp;
} /* End of 'Swap' function */

/* Generate all permutations function.
 * ARGUMENTS:
 *   - position:
 *       INT Pos;
 * RETURNS: None.
 */
VOID Go( INT Pos)
{ 
  INT i;

  if (Pos == N)
  {
    DBL prod;

    /* Obtain next determinant element */
    for (prod = 1, i = 0; i < N; i++)
      prod *= A[i][P[i]];
    Determinant += prod * (2 * (1 - Parity) - 1);
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      if (i != Pos)
      {
        Swap(&P[Pos], &P[i]);
        Parity = !Parity;
      }
      Go(Pos + 1);
      if (i != Pos)
      {
        Swap(&P[Pos], &P[i]);
        Parity = !Parity;
      }
    }
  }
} /* End of 'Go' function */

/* The main program function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID main( VOID )
{
  INT i;

  if (!LoadMatrix("m3.TXT"))
  {
    printf("Error load matrix\n");
    return;
  }

  /* Fill permutation table */
  for (i = 0; i < N; i++)
    P[i] = i;
  Go(0);

  Save();
} /* End of 'main' function */