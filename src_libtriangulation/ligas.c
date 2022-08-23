/**
 * @file ligas.c
 * @date 02/10/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Ligas2013Simple.
*/
#include  <math.h>
#include  "const.h"
#include  "ligas.h"

tfloat triangulationLigas(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat cot_alpha = Cot( alpha2 - alpha1 ) ; /* alpha */
	tfloat cot_beta  = Cot( alpha3 - alpha2 ) ; /* beta */
	cot_alpha = adjust_value_to_bounds( cot_alpha , COT_MAX ) ;
	cot_beta  = adjust_value_to_bounds( cot_beta  , COT_MAX ) ;
  
  tfloat A1 = -x1 - x2 ;
  tfloat A2 = -y1 - y2 ;
  tfloat A3 = x1 * x2 + y1 * y2 ;
  tfloat A4 = y1 - y2 ;
  tfloat A5 = x2 - x1 ;
  tfloat A6 = x1 * y2 - x2 * y1 ;
  
  tfloat B1 = -x2 - x3 ;
  tfloat B2 = -y2 - y3 ;
  tfloat B3 = x2 * x3 + y2 * y3 ;
  tfloat B4 = y2 - y3 ;
  tfloat B5 = x3 - x2 ;
  tfloat B6 = x2 * y3 - x3 * y2 ;
  
  tfloat a = A1 - A4 * cot_alpha ;
  tfloat b = A2 - A5 * cot_alpha ;
  tfloat c = A3 - A6 * cot_alpha ;
  tfloat d = B1 - B4 * cot_beta ;
  tfloat e = B2 - B5 * cot_beta ;
  tfloat f = B3 - B6 * cot_beta ;
  
  tfloat A = a - d ;
  tfloat B = b - e ;
  tfloat C = c - f ;
  
  tfloat AA = A*A ;
  tfloat BB = B*B ;
  tfloat AB = A*B ;
  
  tfloat D = AA + BB ;
  
  if ( A != 0.0 )
  {
    *y = ( ( -2*C*B - b*AA + a*AB ) / D ) - y2 ;
    *x = ( -B*(*y) - C) / A ;
  }
  else
  {
    *x = ( ( -2*C*A - a*BB + b*AB ) / D ) - x2 ;
    *y = ( -A*(*x) - C) / B ;
  }
  
  return D ;
}

