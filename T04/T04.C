/* FILE NAME: PERM04.C
 * PROGRAMMER: PL5
 * DATE: 02.06.2020 
 * PURPOSE: MATH TESTING
 */

#include <stdio.h>
#include <windows.h>
#define MAX 3

BOOL IsParity = 1; 
INT P[MAX];

VOID Store( VOID );
VOID Go( INT Pos );

/* function that swaps elements
 * ARGUMENTS:
 * - elements which are swapped
 *     int x, y;
 * RETURNS:
 *   NONE 
 */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
} /* End of 'Swap' function */

/* function that makes new perm
 * ARGUMENTS:
 * - Position:
 *     int Pos;
 * RETURNS:
 *   NONE */
VOID Go( INT Pos )
{ 
  INT i, x;
  BOOL save_parity = 1;

  if (Pos == MAX)
    Store();
  else
  {
    save_parity = IsParity;
    Go(Pos + 1);
    for (i = Pos + 1; i < MAX; i++)
    {
      /* Put in Pos element i*/
      Swap(&P[Pos], &P[i]);
      IsParity = !IsParity;
      Go(Pos + 1);
    }
    x = P[Pos];
    for (i = Pos + 1; i < MAX; i++)
      P[i - 1] = P[i];
    P[MAX - 1] = x;
    IsParity = save_parity;
  }
} /* End of Go function */


/* function that saves reult
 * ARGUMENTS: NONE
 * RETURNS: NONE
*/
VOID Store( VOID )
{ 
  INT i;

  FILE *F = fopen("PERM.TXT", "a");
 
  if (F != NULL) 
  {
    for (i = 0; i < MAX; i++)
      fprintf(F, "%d ", P[i]);
    fprintf(F, "%s", IsParity ? "even" : "odd");
    fprintf(F, "\n");
    fclose(F);
  }

  else 
    return;
} /* End of Save function */

/* the main function of the programm */
VOID main( VOID )
{
  int i;

  for(i = 0; i < MAX; i++)
    P[i] = i + 1;
  Go(0);
} /* End of main function */