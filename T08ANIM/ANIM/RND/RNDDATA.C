/* FILE NAME: RNDDATA.C
 * PROGRAMMER: PL5
 * DATE: 06.06.2020
 * PURPOSE: 3D animation project.
 *          Render system global data
 */

#include "rnd.h"

HWND PL5_hRndWnd;        /* Work window handle */
HDC PL5_hRndDCFrame;     /* Work window memory device context  */
HBITMAP PL5_hRndBmFrame; /* Work window background bitmap handle */
INT PL5_RndFrameH, PL5_RndFrameW; /* Work window size */

DBL
  PL5_RndProjSize,  /* Project plane fit square */
  PL5_RndProjDist,  /* Distance to project plane from viewer (near) */
  PL5_RndProjFarClip;  /* Distance to project far clip plane (far) */

MATR
  PL5_RndMatrView, /* View coordinate system matrix */
  PL5_RndMatrProj, /* Projection coordinate system matrix */
  PL5_RndMatrVP;   /* Stored (View * Proj) matrix */

/* END OF 'RNDDATA.C' FILE */