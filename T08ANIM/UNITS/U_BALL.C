/* FILE NAME: U_BALLS.C
 * PROGRAMMER: PL5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "units.h"

typedef struct tagpl5UNIT_BALL
{
  UNIT_BASE_FIELDS;
  pl5PRIM Ball;
} pl5UNIT_BALL;

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_BALL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitClose( pl5UNIT_BALL *Uni, pl5ANIM *Ani )
{
  PL5_RndPrimFree(&Uni->Ball);
} /* End of 'PL5_UnitClose' function */

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_BALL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitInit( pl5UNIT_BALL *Uni, pl5ANIM *Ani )
{
  PL5_RndPrimCreateSphere(&Uni->Ball, VecSet(0, 0, 0), 1, 30, 30);
} /* End of 'PL5_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_BALL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitResponse( pl5UNIT_BALL *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_BALL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitRender( pl5UNIT_BALL *Uni, pl5ANIM *Ani )
{
  PL5_RndPrimDraw(&Uni->Ball, MatrRotateX(PL5_Anim.Time));
} /* End of 'PL5_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (pl5UNIT *) pointer to created unit.
 */
pl5UNIT * PL5_UnitCreateBall( VOID )
{
  pl5UNIT_BALL *Uni;

  if ((Uni = (pl5UNIT_BALL *)PL5_AnimUnitCreate(sizeof(pl5UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)PL5_UnitInit;
  Uni->Response = (VOID *)PL5_UnitResponse;
  Uni->Render = (VOID *)PL5_UnitRender;
  return (pl5UNIT *)Uni;
} /* End of 'PL5_UnitCreateBall' function */

/* END OF 'U_BALLS.C' FILE */