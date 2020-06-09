/* FILE NAME: INPUT.C
 * PROGRAMMER: PL5
 * LAST UPDATE: 09.06.2020
 * PURPOSE: Simple WinAPI animation project.
 *          Iput system.
 */

#include "anim.h"

/* Initilizate keyboard function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID PL5_AnimKeyboardInit( VOID )
{
} /* End of 'pl5_AnimKeyboardInit' function */

VOID PL5_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(PL5_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    PL5_Anim.Keys[i] >>= 7;
    PL5_Anim.KeysClick[i] = PL5_Anim.Keys[i] && !PL5_Anim.KeysOld[i];
  }
  memcpy(PL5_Anim.KeysOld, PL5_Anim.Keys, 256);
}

/* Initilizate mouse function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID PL5_AnimMouseInit( VOID )
{
} /* End of 'PL5_AnimMouseInit' function */

VOID PL5_AnimMouseResponse( VOID )
{
  POINT pt;

  PL5_Anim.Mdz = PL5_MouseWheel;
  PL5_Anim.Mz += PL5_MouseWheel;
  PL5_MouseWheel = 0;

  GetCursorPos(&pt);
  ScreenToClient(PL5_Anim.hWnd, &pt);
  PL5_Anim.Mdx = pt.x - PL5_Anim.Mx;
  PL5_Anim.Mdy = pt.y - PL5_Anim.My;
  PL5_Anim.Mx = pt.x;
  PL5_Anim.My = pt.y;
}

/* Initilizate joystick function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID PL5_AnimJoystickInit( VOID )
{
} /* End of 'PL5_AnimJoystickInit' function */

static VOID PL5_AnimJoystickResponse( VOID )
{
}

/* END OF 'INPUT.C' FILE */