/* FILE NAME: UNIT.C
 * PROGRAMMER: PL5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitInit( pl5UNIT *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitClose( pl5UNIT *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitResponse( pl5UNIT *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitRender( pl5UNIT *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (pl5UNIT *) pointer to created unit.
 */
pl5UNIT * PL5_AnimUnitCreate( INT Size )
{
  pl5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(pl5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = PL5_UnitInit;
  Uni->Close = PL5_UnitClose;
  Uni->Response = PL5_UnitResponse;
  Uni->Render = PL5_UnitRender;

  return Uni;
} /* End of 'PL5_AnimUnitCreate' function */

/* END OF 'UNIT.C' FILE */