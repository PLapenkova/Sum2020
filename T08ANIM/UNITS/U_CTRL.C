/* FILE NAME  : U_CTRL.C
 * PROGRAMMER : PL5
 * LAST UPDATE: 09.06.2020
 * PURPOSE    : Simple WinAPI animation project.
 *              Control unit sample.
 */

#include <stdio.h>

#include "units.h"

/* Animation unit representation type */
typedef struct tagpl5UNIT_CTRL
{
  UNIT_BASE_FIELDS;
  DBL
    Distance,      /* Camera offset */
    RotateAngle,   /* Camera rotate angle */
    ElevatorAngle; /* Camera elevator angle */
} pl5UNIT_CTRL;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_CTRL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitInit( pl5UNIT_CTRL *Uni, pl5ANIM *Ani )
{
  Uni->RotateAngle = 30;
  Uni->ElevatorAngle = 47;
  Uni->Distance = 4;
} /* End of 'PL5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_CTRL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitClose( pl5UNIT_CTRL *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_CTRL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitResponse( pl5UNIT_CTRL *Uni, pl5ANIM *Ani )
{
  VEC L = VecSet(0, 0, Uni->Distance);
  static CHAR Buf[102];

  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick[VK_RETURN] && Ani->Keys[VK_MENU])
    PL5_FlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    ;//PL5_AnimDoExit();

  if (Ani->Keys[VK_LBUTTON])
  {
    Uni->Distance += Ani->DeltaTime * Ani->Mdz * 0.3;
    Uni->RotateAngle += Ani->DeltaTime * 30 * Ani->Mdx;
    Uni->ElevatorAngle += Ani->DeltaTime * 30 * Ani->Mdy;
  }
  L = PointTransform(L,
    MatrMulMatr3(MatrRotateZ(-Uni->Distance),
                 MatrRotateX(-Uni->ElevatorAngle),
                 MatrRotateY(-Uni->RotateAngle)));
  PL5_RndCamSet(L, VecSet(0, 0, 0), VecSet(0, 1, 0));

  SetTextColor(Ani->hDC, RGB(0, 255, 255));
  SetBkMode(Ani->hDC, TRANSPARENT);
  TextOut(Ani->hDC, 0, 0, Buf, sprintf(Buf, "FPS: %.3f", Ani->FPS));
} /* End of 'PL5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       pl5UNIT_CTRL *Uni;
 *   - animation context:
 *       pl5ANIM *Ani;
 * RETURNS: None.
 */
static VOID PL5_UnitRender( pl5UNIT_CTRL *Uni, pl5ANIM *Ani )
{
} /* End of 'PL5_UnitRender' function */

/* Control unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (pl5UNIT_CTRL *) pointer to created unit.
 */
pl5UNIT * PL5_UnitCreateControl( VOID )
{
  pl5UNIT_CTRL *Uni;

  /* Memory allocation */
  if ((Uni = (pl5UNIT_CTRL *)PL5_AnimUnitCreate(sizeof(pl5UNIT_CTRL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)PL5_UnitInit;
  Uni->Close = (VOID *)PL5_UnitClose;
  Uni->Response = (VOID *)PL5_UnitResponse;
  Uni->Render = (VOID *)PL5_UnitRender;
  return (pl5UNIT *)Uni;
} /* End of 'PL5_UnitCreateControl' function */

/* END OF 'U_CTRL.C' FILE */