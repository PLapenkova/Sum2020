/* FILE NAME: UNITS.H
 * PROGRAMMER: PL5
 * DATE: 09.06.2020
 * PURPOSE: WinAPI windowed application sample.
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "../def.h"
#include "../anim/anim.h"

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (pl5UNIT *) pointer to created unit.
 */
pl5UNIT * PL5_UnitCreateBall( VOID );

/* Control unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (pl5UNIT_CTRL *) pointer to created unit.
 */
pl5UNIT * PL5_UnitCreateControl( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */