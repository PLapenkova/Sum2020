#include "MTH.H"
#include "GLOBE.H"
#include "TIMER.H"
#include <time.h>

VEC G[GLOBE_H][GLOBE_W];

/* Store coord syst center */
static INT CenterX, CenterY;

/* Fill geometry func
 * ARGUMENTS:
 *   -Coordinates
 *      DBL Xc, DBL Yc; 
 *   -rotation angle in degrees:
 *      DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector
 */
VOID GlobeSet( DBL Xc, DBL Yc, DBL R )
{
  INT i, j;
  DOUBLE t, p;

  CenterX = (INT)Xc, CenterY = (INT)Yc;
  for (i = 0, t = 0; i < GLOBE_H; i++, t += PI / (GLOBE_H - 1))
    for (j = 0, p = 0; j < GLOBE_W; j++, p += 2 * PI / (GLOBE_W - 1))
     { 
        G[i][j].X = R * cos(p) * sin(t);
        G[i][j].Y = R * cos(t);
        G[i][j].Z = R * sin(p) * sin(t);
     }
} /* end globeset func */

/* Draw Globe func
 * ARGUMENTS:
 *   -hDC
 *      HDC hDC;
 */
VOID GlobeDraw( HDC hDC )
{
  DBL s = 5, k;
  INT i, j;
  DBL z[GLOBE_H][GLOBE_W];
  static POINT pnt[GLOBE_H][GLOBE_W]; 
  MATR m;
  DBL
    Size = 1.0, Ws = CenterX * 2, Hs = CenterY * 2,
    Wp = 1.0, Hp = 1.0, ProjDist = 1.0;

  

  /* recalculate Wp and Hp */
  if (Ws > Hs)
    Wp = Size * Ws / Hs, Hp = Size;
  else
    Hp = Size * Hs / Ws, Wp = Size;

  /* setup transformation */
  m = MatrMulMatr3(MatrRotateY(GLB_Time * 8), 
                   MatrView(VecSet(sin(GLB_Time * 2.26) * 3, sin(GLB_Time * 2) * 5,5), VecSet(0, 0, 0), VecSet(0, 1, 0)),
                   MatrFrustum(-Wp / 2, Wp / 2 , -Hp / 2, Hp / 2, Size, 400));

  /*m = MatrMulMatr3(MatrRotateY(GLB_Time * 35), 
    MatrView(VecSet(cos(GLB_Time) * 5, sin(GLB_Time) * 2, 2), VecSet(0, 0, 0), VecSet(0, 1, 0)),
    MatrFrustum(-Wp / 2, Wp / 2, -Hp / 2, Hp / 2, Size, 100)); */
 
  
  /* initialize structures */
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
    {  
       VEC v;

       /* World Transform */
       v = VecMulMatr(G[i][j], m);

       z[i][j] = v.Z;

       /* parallel projection */       
       pnt[i][j].x = (INT)((v.X + 1) * Ws / 2.0),
       pnt[i][j].y = (INT)((-v.Y + 1) * Hs / 2.0); 
    }

  /* draw using dots */
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  for (i = 0; i < GLOBE_H; i++)
    for (j = 0; j < GLOBE_W; j++)
     if (z[i][j] > 0)
        ;//Ellipse(hDC, pnt[i][j].x - s, pnt[i][j].y - s, pnt[i][j].x + s, pnt[i][j].y + s); 
  
  /* linear draw */
  /*
  for (i = 0; i < GLOBE_H; i++)
  { 
    MoveToEx(hDC, pnt[i][0].x, pnt[i][0].y, NULL);
    for (j = 1; j < GLOBE_W; j++)
    {       
      LineTo(hDC, pnt[i][j].x, pnt[i][j].y);
    }
  } 
  for (j = 0; j < GLOBE_W; j++)
  { 
    MoveToEx(hDC, pnt[0][j].x, pnt[0][j].y, NULL);
    for (i = 1; i < GLOBE_H; i++)
    {       
      LineTo(hDC, pnt[i][j].x, pnt[i][j].y);
    }
  }*/

  /* polygon draw */
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SelectObject(hDC, GetStockObject(NULL_PEN));
  srand(30);
  for (i = 0; i < GLOBE_H - 1; i++)
    for (j = 0; j < GLOBE_W - 1; j++)
    { 
        POINT ps[4];
        ps[0] = pnt[i][j]; 
        ps[1] = pnt[i][j + 1]; 
        ps[2] = pnt[i + 1][j + 1]; 
        ps[3] = pnt[i + 1][j]; 
        
        SetDCBrushColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
        
        k = ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
             (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
             (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
             (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y));
        if (k <= 0)
        {
          SetDCPenColor(hDC, RGB(50, 50, 0));
          Polygon(hDC, ps, 4);
        }
    }
} /*end drawglobe func */