/* FILE NAME: ANIM.C
 * PROGRAMMER: PL5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#include "anim.h"

/* Global animation context */
pl5ANIM PL5_Anim;

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID PL5_AnimResize( INT W, INT H )
{
  PL5_Anim.H = H;
  PL5_Anim.W = W;
  PL5_RndResize(W, H);
} /* End of 'PL5_AnimResize' function */

/* Copy frame function.
 * ARGUMENTS:
 *   - window context:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID PL5_AnimCopyFrame( HDC hDC )
{
  PL5_RndCopyFrame(hDC);
  PL5_Anim.hDC = hDC;
} /* End of 'PL5_AnimCopyFrame' function */

/* Add unit function.
 * ARGUMENTS:
 *   - unit:
 *       pl5UNIT *Uni.
 * RETURNS: None.
 */
VOID PL5_AnimUnitAdd( pl5UNIT *Uni )
{
  if (PL5_Anim.NumOfUnits < PL5_MAX_UNITS)
    PL5_Anim.Units[PL5_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &PL5_Anim);
} /* End of 'PL5_AnimUnitAdd' function */

/* Initilizate animation function.
 * ARGUMENTS:
 *   - window handel:
 *       HWND hWnd.
 * RETURNS: None.
 */
VOID PL5_AnimInit( HWND hWnd )
{
  PL5_RndInit(hWnd);
  PL5_TimerInit();

  PL5_Anim.hWnd = hWnd;
  PL5_Anim.hDC = PL5_hRndDCFrame;
  PL5_Anim.H = PL5_RndFrameH;
  PL5_Anim.W = PL5_RndFrameW;
} /* End of 'PL5_RndInit' function */

/* Animation system close function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID PL5_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < PL5_Anim.NumOfUnits; i++)
  {
    PL5_Anim.Units[i]->Close(PL5_Anim.Units[i], &PL5_Anim);
    free(PL5_Anim.Units[i]);
  }
  PL5_Anim.NumOfUnits = 0;
  PL5_RndClose();
} /* End of 'PL5_AnimClose' function */

/* Animation system render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_AnimRender( VOID )
{
  INT i;

  PL5_TimerResponse();
  PL5_AnimKeyboardResponse();
  PL5_AnimMouseResponse();

  for (i = 0; i < PL5_Anim.NumOfUnits; i++)
    PL5_Anim.Units[i]->Response(PL5_Anim.Units[i], &PL5_Anim);

  PL5_RndStart();
  for (i = 0; i < PL5_Anim.NumOfUnits; i++)
    PL5_Anim.Units[i]->Render(PL5_Anim.Units[i], &PL5_Anim);
  PL5_RndEnd();
} /* End of 'PL5_AnimRender' function */

/* Turn full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_FlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  IsFullScreen = !IsFullScreen;
  if (!IsFullScreen)
  {
    HMONITOR hmon;
    MONITORINFO moninfo;
    RECT rc;

    /* Goto fullscreen mode */
    GetWindowRect(PL5_Anim.hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(PL5_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* Get monitor information */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, &moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(PL5_Anim.hWnd, GWL_STYLE), FALSE);
    SetWindowPos(PL5_Anim.hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Restore window size and position */
    SetWindowPos(PL5_Anim.hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
} /* End of 'FlipFullScreen' function */

/* END OF 'ANIM.C' FILE */