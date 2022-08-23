/**
 * @file lukic.c 
 * @date 04/09/2012
 * @author Vincent Pierlot
 *
 * The algorithm was implemented after \cite Lukic2011AnAutonomous.
 * This algorithm is not general like the other ones; they are constraints on the beacon locations:
 *  x1 = 0, y1 = 0, x3 > 0, x2 = -x3, y2 = y3.
*/
#include  <math.h>
#include  "const.h"
#include  "lukic.h"

tfloat triangulationLukicOriginal(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
	tfloat cot_phi1 = adjust_value_to_bounds( 1 / tan( alpha3 - alpha1 ) , COT_MAX ) ;
	tfloat cot_phi2 = adjust_value_to_bounds( 1 / tan( alpha1 - alpha2 ) , COT_MAX ) ;
  
  tfloat L1 = x3 - x2 ;
  tfloat L2 = y2 ;
  
  tfloat cx1 = L1/4 - L2*cot_phi1/2 ;
  tfloat cy1 = L2/2 + L1*cot_phi1/4 ;
  
  tfloat cx2 = -L1/4 + L2*cot_phi2/2 ;
  tfloat cy2 =  L2/2 + L1*cot_phi2/4 ;
  
  tfloat N = cx1 * cy2 - cx2 * cy1 ;
  tfloat D = (cy2 - cy1)*(cy2 - cy1) + (cx2 - cx1)*(cx2 - cx1) ;
  
  tfloat K = 2 * N / D ;
  
  *x = K * ( cy2 - cy1 ) ;
  *y = K * ( cx1 - cx2 ) ;
  
  return D;
}

tfloat triangulationLukic(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
	tfloat cot_phi1 = adjust_value_to_bounds( 1 / tan( alpha3 - alpha1 ) , COT_MAX ) ;
	tfloat cot_phi2 = adjust_value_to_bounds( 1 / tan( alpha1 - alpha2 ) , COT_MAX ) ;
  
  tfloat L1 = ( x3 - x2 ) / 2 ;
  tfloat L2 = y2 ;
  
  tfloat cx1 = L1 - L2*cot_phi1 ;
  tfloat cy1 = L2 + L1*cot_phi1 ;
  
  tfloat cx2 = -L1 + L2*cot_phi2 ;
  tfloat cy2 =  L2 + L1*cot_phi2 ;
  
  tfloat N = cx1 * cy2 - cx2 * cy1 ;
  tfloat D = (cy2 - cy1)*(cy2 - cy1) + (cx2 - cx1)*(cx2 - cx1) ;
  
  tfloat K = N / D ;
  
  *x = K * ( cy2 - cy1 ) ;
  *y = K * ( cx1 - cx2 ) ;
  
  return D;
}

