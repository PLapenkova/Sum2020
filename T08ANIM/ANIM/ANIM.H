/* FILE NAME: ANIM.H
 * PROGRAMMER: PL5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "../def.h"
#include "RND/rnd.h"

#define PL5_MAX_UNITS 1000
#define UNIT_BASE_FIELDS \
  VOID (*Init)( pl5UNIT *Uni, pl5ANIM *Ani );      \
  VOID (*Close)( pl5UNIT *Uni, pl5ANIM *Ani );     \
  VOID (*Response)( pl5UNIT *Uni, pl5ANIM *Ani );  \
  VOID (*Render)( pl5UNIT *Uni, pl5ANIM *Ani )

typedef struct tagpl5UNIT pl5UNIT;
typedef struct tagpl5ANIM pl5ANIM;
struct tagpl5UNIT
{
  UNIT_BASE_FIELDS;
};
/* Animation context representation type */
struct tagpl5ANIM
{
  /* Window data */
  HWND hWnd;                     /* Work window handle */
  HDC hDC;                       /* Back buffer context */
  INT W, H;                      /* Back buffer size */

  /* Units array data */
  pl5UNIT *Units[PL5_MAX_UNITS]; /* Animation units array */
  INT NumOfUnits;                /* Animation units array size */

  /* Timer handle data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */

  BOOL
    IsPause;                     /* Pause flag */

  /* Keyboard handle data */
  BYTE
    Keys[256],                   /* Keyboard state (true if key pressed) */
    KeysOld[256],                /* Previous frame keyboard state */
    KeysClick[256];              /* Key 'one-click' info */

  /* Mouse handle data */
  INT
    Mx, My, Mz,                  /* Absolute mouse coordinates */
    Mdx, Mdy, Mdz;               /* Relative mouse coordinates */
};

extern pl5ANIM PL5_Anim;
extern INT PL5_MouseWheel;

/* Change window size function.
 * ARGUMENTS:
 *   - window size:
 *       INT W, INT H
 * RETURNS: None.
 */
VOID PL5_AnimResize( INT W, INT H );

/* Copy frame function.
 * ARGUMENTS:
 *   - window context:
 *       HDC hDC.
 * RETURNS: None.
 */
VOID PL5_AnimCopyFrame( HDC hDC );

/* Add unit function.
 * ARGUMENTS:
 *   - unit:
 *       pl5UNIT *Uni.
 * RETURNS: None.
 */
VOID PL5_AnimUnitAdd( pl5UNIT *Uni );

/* Initilizate animation function.
 * ARGUMENTS:
 *   - window handel:
 *       HWND hWnd.
 * RETURNS: None.
 */
VOID PL5_AnimInit( HWND hWnd );

/* Animation system close function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID PL5_AnimClose( VOID );

/* Animation system render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_AnimRender( VOID );

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (pl5UNIT *) pointer to created unit.
 */
pl5UNIT * PL5_AnimUnitCreate( INT Size );

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_TimerInit( VOID );

/* Timer interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_TimerResponse( VOID );

/* Turn full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID PL5_FlipFullScreen( VOID );

VOID PL5_AnimKeyboardResponse( VOID );
VOID PL5_AnimMouseResponse( VOID );
#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */