/* FILE NAME: RND.H
 * PROGRAMMER: PL5
 * DATE: 05.06.2020
 * PURPOSE: 3D animation project.
 *          Common declaration module.
 */

#ifndef __RND_H_
#define __RND_H_

#include "../../def.h"

/* render data */
extern HWND PL5_hRndWnd;        /* Work window handle */
extern HDC PL5_hRndDCFrame;     /* Work window memory device context  */
extern HBITMAP PL5_hRndBmFrame; /* Work window background bitmap handle */
extern INT PL5_RndFrameH, PL5_RndFrameW; /* Work window size */

extern DBL
  PL5_RndProjSize,  /* Project plane fit square */
  PL5_RndProjDist,  /* Distance to project plane from viewer (near) */
  PL5_RndProjFarClip;  /* Distance to project far clip plane (far) */


extern MATR
  PL5_RndMatrView, /* View coordinate system matrix */
  PL5_RndMatrProj, /* Projection coordinate system matrix */
  PL5_RndMatrVP;   /* Stored (View * Proj) matrix */

/* vertex type */
typedef struct tagpl5VERTEX
{
  VEC P;  /* Vertex position */
} pl5VERTEX;

/* primitiv type */
typedef struct tagpl5PRIM
{
  pl5VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} pl5PRIM;

/* Render systen initialization function.
 * ARGUMENTS:
 *   - HWND:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID PL5_RndInit( HWND hWnd );

/* Render systen initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_RndClose( VOID );

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID PL5_RndResize( INT W, INT H );

/* Change window size function.
 * ARGUMENTS:
 *   - window:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID PL5_RndCopyFrame( HDC hDC );

/* Start draw function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_RndStart( VOID );

/* End draw function 
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID PL5_RndEnd( VOID );

/* Create camera function.
 * ARGUMENTS: None.
 *
 * RETURNS: None.
 */
VOID PL5_RndProjSet( VOID );

/* Set camera function.
 * ARGUMENTS:
 *   - parametr of located:
 *       VEC Loc, VEC At, VEC Up.
 * RETURNS: None.
 */
VOID PL5_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Create primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       pl5PRIM *Pr.
 *   - number of vertices:
 *       INT NoofV.
 *   - number of index:
 *       INT NoofI.
 * RETURNS:
 *   (BOOL) work.
 */
BOOL PL5_RndPrimCreate( pl5PRIM *Pr, INT NoofV, INT NoofI );

/* Delete primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       pl5PRIM *Pr.
 * RETURNS: None.
 */
VOID PL5_RndPrimFree( pl5PRIM *Pr );

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive:
 *       pl5PRIM *Pr.
 *   - wotld matrix:
 *       MATR Wolrd.
 * RETURNS:
 *   (BOOL) work.
 */
VOID PL5_RndPrimDraw( pl5PRIM *Pr, MATR World);

/* Create prim of sphere function 
 * ARGUMENTS:
 *   - prim struct:
 *       pl5PRIM *Pr.
 *   - centr coordinate:
 *       VEC C.
 *   - radius
 *       DBL R.
 *   - number of segments.
 *       INT SplitW, INT SplitH
 * RETURNS:
 *   (BOOL) work.
 */
BOOL PL5_RndPrimCreateSphere( pl5PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );

BOOL PL5_RndPrimCreateTorus( pl5PRIM *Pr, VEC C, DBL R, DBL r, INT SplitW, INT SplitH );

BOOL PL5_RndPrimCreateConeTorus( pl5PRIM *Pr, VEC C, DBL R, DBL r, INT SplitW, INT SplitH );

/* Load primitive from .OBJ file function.
 * ARGUMENTS:
 *   - pointer to primitive to be build:
 *       pl5PRIM *Pr;
 *   - .OBJ file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is successful, FALSE otherwise.
 */
BOOL PL5_RndPrimLoad( pl5PRIM *Pr, CHAR *FileName );

#endif /* __DEF_H_ */

/* END OF 'RND.H' FILE */