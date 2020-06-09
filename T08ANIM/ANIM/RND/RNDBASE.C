/* FILE NAME: RNDBASE.C
 * PROGRAMMER: PL5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system render handle function
 */

#include "rnd.h"

/* Render system close function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID PL5_RndInit( HWND hWnd )
{
  HDC hDC;

  PL5_hRndWnd = hWnd;

  /* Create fram buffer */
  hDC = GetDC(hWnd);
  PL5_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
  PL5_hRndBmFrame = NULL;

  /* default parametrs */
  PL5_RndFrameH = 102;
  PL5_RndFrameW = 102;

  PL5_RndProjSize = PL5_RndProjDist = 1.0;
  PL5_RndProjFarClip = 300;

  PL5_RndProjSet();
  PL5_RndCamSet(VecSet(3, 3, 3), VecSet(0, 0, 0), VecSet(0, 1, 0));
} /* End of 'PL5_RndInit' function */

/* Render systen initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_RndClose( VOID )
{
  if (PL5_hRndBmFrame != NULL)
    DeleteObject(PL5_hRndBmFrame);
  DeleteDC(PL5_hRndDCFrame);
} /* End of 'PL5_RndClose' function */

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID PL5_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(PL5_hRndWnd);

  if (PL5_hRndBmFrame)
    DeleteObject(PL5_hRndBmFrame);
  PL5_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(PL5_hRndWnd, hDC);
  SelectObject(PL5_hRndDCFrame, PL5_hRndBmFrame);

  /* save size */
  PL5_RndFrameW = W;
  PL5_RndFrameH = H;

  /* recalculat project */
  PL5_RndProjSet();
} /* End of 'PL5_RndResize' function */

/* Copy frame function.
 * ARGUMENTS:
 *   - window context:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID PL5_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, PL5_RndFrameW, PL5_RndFrameH, PL5_hRndDCFrame, 0, 0, SRCCOPY);
} /* End of 'PL5_RndCopyFrame' function */

/* Start draw function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_RndStart( VOID )
{
  SelectObject(PL5_hRndDCFrame, GetStockObject(NULL_PEN));
  SelectObject(PL5_hRndDCFrame, GetStockObject(WHITE_BRUSH));
  Rectangle(PL5_hRndDCFrame, 0, 0, PL5_RndFrameW + 1, PL5_RndFrameH + 1);
  SelectObject(PL5_hRndDCFrame, GetStockObject(BLACK_PEN));
} /* End of 'PL5_RndStart' function */

/* End draw function 
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID PL5_RndEnd( VOID )
{
} /* End of 'PL5_RndEnd' function */

/* Create camera function.
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID PL5_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = PL5_RndProjSize / 2;

  /* Correct aspect ratio */
  if (PL5_RndFrameW > PL5_RndFrameH)
    rx *= (DBL)PL5_RndFrameW / PL5_RndFrameH;
  else
    ry *= (DBL)PL5_RndFrameH / PL5_RndFrameW;

  PL5_RndMatrProj = MatrFrustum(-rx, rx, -ry, ry, 
                      PL5_RndProjDist, PL5_RndProjFarClip);
  PL5_RndMatrVP = MatrMulMatr(PL5_RndMatrView, PL5_RndMatrProj);
} /* End of 'PL5_RndProjSet' function */

/* Set camera function.
 * ARGUMENTS:
 *   - parametr of located:
 *       VEC Loc, VEC At, VEC Up.
 * RETURNS: None.
 */
VOID PL5_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  PL5_RndMatrView = MatrView(Loc, At, Up);
  PL5_RndMatrVP = MatrMulMatr(PL5_RndMatrView, PL5_RndMatrProj);
} /* End of 'PL5_RndCamSet' function */

/* END OF 'RNDBASE.C' FILE */