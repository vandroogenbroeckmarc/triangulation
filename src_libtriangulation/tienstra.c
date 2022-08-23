/**
 * @file tienstra.c
 * @date 02/10/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Porta2009Concise.
*/
#include  <math.h>
#include  "const.h"
#include  "tienstra.h"

tfloat triangulationTienstra(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ;
  tfloat alpha23 = alpha3 - alpha2 ;
  tfloat alpha31 = alpha1 - alpha3 ;
  
  tfloat L12_2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ;
  tfloat L23_2 = (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ;
  tfloat L13_2 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) ;
  tfloat L12 = sqrt( L12_2 ) ;
  tfloat L23 = sqrt( L23_2 ) ;
  tfloat L13 = sqrt( L13_2 ) ;
  
  tfloat A123 = acos( ( L12_2 + L23_2 - L13_2 ) / ( 2 * L12 * L23 ) ) ;
  tfloat A213 = acos( ( L12_2 + L13_2 - L23_2 ) / ( 2 * L12 * L13 ) ) ;
  tfloat A132 = acos( ( L13_2 + L23_2 - L12_2 ) / ( 2 * L13 * L23 ) ) ;
  
  tfloat cotA123 = Cot( A123 ) ;
  tfloat cotA213 = Cot( A213 ) ;
  tfloat cotA132 = Cot( A132 ) ;
  
  tfloat cot_alpha12 = Cot( alpha12 ) ;
  tfloat cot_alpha23 = Cot( alpha23 ) ;
  tfloat cot_alpha31 = Cot( alpha31 ) ;
  
  tfloat f1 = 1 / ( cotA213 - cot_alpha23 ) ;
  tfloat f2 = 1 / ( cotA123 - cot_alpha31 ) ;
  tfloat f3 = 1 / ( cotA132 - cot_alpha12 ) ;
  tfloat F  = f1 + f2 + f3 ;
  
  *x = ( f1 * x1 + f2 * x2 + f3 * x3 ) / F ;
  *y = ( f1 * y1 + f2 * y2 + f3 * y3 ) / F ;
  
  return F ;
}

