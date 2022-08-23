/**
 * @file hmam.c 
 * @date 05/09/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Hmam2007Mobile.
 *  !!! FOR NOW IT DOES NOT WORK FOR ALL CASES !!!
*/
#include  <math.h>
#include  "const.h"
#include  "hmam.h"

tfloat triangulationHmam(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat lambda12 = alpha2 - alpha1 ;
  tfloat lambda23 = alpha3 - alpha2 ;
  
	tfloat mu = Sin( lambda12 ) / d12 ;
	tfloat eta = Sin( lambda23 ) / d23 ;
	
	tfloat phi = atan2( (y1-y2) , (x1-x2) ) ;
	
	tfloat beta = phi - atan2( (y3-y2) , (x3-x2) ) ;
	
	tfloat r2 = fabs( Sin( beta + lambda12 + lambda23 ) ) / sqrt( mu*mu + eta*eta + 2*mu*eta*Cos( beta + lambda12 + lambda23 ) ) ;
	
	tfloat theta12 = asin( mu*r2 ) ;
	
	tfloat beta12 = PI - lambda12 - theta12 ;
  
  *x = x2 + r2 * Cos( phi - beta12 ) ;
  *y = y2 + r2 * Sin( phi - beta12 ) ;
  
  return beta;
}

