/**
 * @file easton.c 
 * @date 05/09/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Easton2006AGaussian.
*/
#include  <math.h>
#include  "const.h"
#include  "easton.h"

tfloat triangulationEaston(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
	tfloat tAB = adjust_value_to_bounds( Tan( alpha1 - alpha2 ) , COT_MAX ) ;
	tfloat tAC = adjust_value_to_bounds( Tan( alpha1 - alpha3 ) , COT_MAX ) ;
	
	tfloat theta = -alpha1 + atan2( (x2*tAB*tAC + y2*tAC - y1*tAC - x3*tAB*tAC - y3*tAB + y1*tAB) , (x2*tAC - y2*tAB*tAC - x1*tAC - x3*tAB + y3*tAB*tAC + x1*tAB)) ;
	
	tfloat tTA = adjust_value_to_bounds( Tan( theta + alpha1 ) , COT_MAX ) ;
	tfloat tTB = adjust_value_to_bounds( Tan( theta + alpha2 ) , COT_MAX ) ;
  
  tfloat K = 1 / ( tTA - tTB ) ;
  
  *x = K * ( y2 - y1 + x1 * tTA - x2 * tTB ) ;
  *y = K * ( tTA * tTB * ( x1 - x2 ) + y2 * tTA - y1 * tTB ) ;
  
  return K;
}

