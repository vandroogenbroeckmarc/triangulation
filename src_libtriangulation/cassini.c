/**
 * @file cassini.c
 * @date 02/10/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Burtch2005ThreePoint.
*/
#include  <math.h>
#include  "const.h"
#include  "cassini.h"

/* ./triangulation -t1 -m20 -1"1000" -2"5300" -3"3100" -4"5000" -5"2200" -6"6300" -a"109.3045" -b"-115.0520" -c"0.0" */
tfloat triangulationCassini(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha = alpha1 - alpha3 ;
  tfloat beta  = alpha3 - alpha2 ;
  
  tfloat cot_alpha = Cot( alpha ) ;
  cot_alpha = adjust_value_to_bounds( cot_alpha , COT_MAX ) ;
  tfloat cot_beta = Cot( beta ) ;
  cot_beta = adjust_value_to_bounds( cot_beta , COT_MAX ) ;
  
  tfloat xH1 = x1 + ( y3 - y1 ) * cot_alpha ;
  tfloat yH1 = y1 + ( x1 - x3 ) * cot_alpha ;
  
  tfloat xH2 = x2 + ( y2 - y3 ) * cot_beta ;
  tfloat yH2 = y2 + ( x3 - x2 ) * cot_beta ;
  
  tfloat AzH1H2 = atan2( (xH2-xH1) , (yH2-yH1) ) ;
  
  tfloat n = Tan( AzH1H2 ) ;
  tfloat inv_n = 1 / n ;
  tfloat N = n + inv_n ;
  
  *x = ( n * x3 + inv_n * xH1 + y3 - yH1 ) / N ;
  *y = ( n * yH1 + inv_n * y3 + x3 - xH1 ) / N ;
  
  return N ;
}

