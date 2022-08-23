/**
 * @file kaestner.c
 * @date 02/10/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Burtch2005ThreePoint.
*/
#include  <stdio.h>
#include  <math.h>
#include  "const.h"
#include  "kaestner.h"

/* ./triangulation -t1 -m20 -1"1000" -2"5300" -3"3100" -4"5000" -5"2200" -6"6300" -a"109.3045" -b"-115.0520" -c"0.0" */
/* TODO: handle special cases */
tfloat triangulationKaestner(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha = alpha1 - alpha3 ; /*printf("alpha = %10.4f\n",alpha*RAD2DEG);*/
  tfloat beta  = alpha3 - alpha2 ; /*printf("beta  = %10.4f\n",beta*RAD2DEG);*/
  
  tfloat sin_alpha = Sin( alpha ) ;
  tfloat sin_beta = Sin( beta ) ;
  
  tfloat a = sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) ) ;
  tfloat b = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat AzAC = atan2( (x3-x1) , (y3-y1) ) ; /*printf("AzAC = %10.4f\n",AzAC*RAD2DEG);*/
  tfloat AzBC = atan2( (x3-x2) , (y3-y2) ) + TWOPI ; /*printf("AzBC = %10.4f\n",AzBC*RAD2DEG);*/
  
  tfloat gamma = AzAC - AzBC + TWOPI ; /*printf("gamma = %10.4f\n",gamma*RAD2DEG);*/
  
  tfloat delta1 = PI - ( alpha + beta + gamma ) / 2 ; /*printf("delta1 = %10.4f\n",delta1*RAD2DEG);*/
  
  tfloat lambda = atan ( a * sin_beta / ( b * sin_alpha ) ) ; /* +/- PI */ /*printf("lambda = %10.4f\n",lambda*RAD2DEG);*/
  
  tfloat delta2 = atan( Tan( delta1 * Cot( QUARTPI + lambda ) ) ) ;  /* +/- PI */ /*printf("delta2 = %10.4f\n",delta2*RAD2DEG);*/
  
  tfloat phi   = delta1 + delta2 ; /*printf("phi = %10.4f\n",phi*RAD2DEG);*/
  
  tfloat c1 = a * Sin( alpha + phi ) / sin_alpha ;
  
  tfloat AzAP = AzAC + phi ;
  
  *x = x1 + c1 * Sin( AzAP ) ;
  *y = y1 + c1 * Cos( AzAP ) ;
  
  return lambda ;
}

