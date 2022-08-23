/**
 * @file collins.c
 * @date 02/10/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Burtch2005ThreePoint.
*/
#include  <math.h>
#include  "const.h"
#include  "collins.h"

/* ./triangulation -t1 -m20 -1"1000" -2"5300" -3"3100" -4"5000" -5"2200" -6"6300" -a"109.3045" -b"-115.0520" -c"0.0" */
tfloat triangulationCollins(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha = alpha1 - alpha3 ;
  tfloat beta  = alpha3 - alpha2 ;
  
  tfloat dAB = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) ;
  
  tfloat AzAB = atan2( (x2-x1) , (y2-y1) ) ;
  tfloat AzAH = AzAB + PI - beta ;
  
  tfloat AHB = beta + alpha - PI ;
  
  tfloat dAH = dAB * Sin( PI - alpha ) / Sin( AHB ) ;
  
  tfloat xH = x1 + dAH * Sin( AzAH ) ;
  tfloat yH = y1 + dAH * Cos( AzAH ) ;
  
  tfloat AzCH = atan2( (xH-x3) , (yH-y3) ) ; AzCH = (AzCH<0) ? AzCH+TWOPI : AzCH ;
  tfloat AzCA = atan2( (x1-x3) , (y1-y3) ) ; AzCA = (AzCA<0) ? AzCA+TWOPI : AzCA ;
  
  tfloat ACP = AzCA - AzCH ;
  
  tfloat phi = PI - alpha - ACP ;
  
  tfloat AzAP = AzCA - PI + phi ;
  tfloat dAC = sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) ) ;
  tfloat dAP = dAC * Sin( ACP ) / Sin( alpha ) ;
  
  *x = x1 + dAP * Sin( AzAP ) ;
  *y = y1 + dAP * Cos( AzAP ) ;
  
  return phi ;
}

