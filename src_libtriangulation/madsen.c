/**
 * @file madsen.c 
 * @date 02/10/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Madsen1998Optimal.
*/
#include  <math.h>
#include  "const.h"
#include  "madsen.h"

tfloat triangulationMadsen(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ;
  tfloat alpha23 = alpha3 - alpha2 ;
  
  tfloat alpha13 = alpha12 + alpha23 ;
  
  tfloat L12_2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ;
  tfloat L23_2 = (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ;
  tfloat L13_2 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) ;
  tfloat L12 = sqrt( L12_2 ) ;
  tfloat L23 = sqrt( L23_2 ) ;
  tfloat L13 = sqrt( L13_2 ) ;
  
  tfloat cosA123 = ( L12_2 + L23_2 - L13_2 ) / ( 2 * L12 * L23 ) ;
  tfloat cosA213 = ( L12_2 + L13_2 - L23_2 ) / ( 2 * L12 * L13 ) ;
  tfloat cosA132 = ( L13_2 + L23_2 - L12_2 ) / ( 2 * L13 * L23 ) ;
  
  tfloat A123 = acos( cosA123 ) ;
  tfloat A213 = acos( cosA213 ) ;
  tfloat A132 = acos( cosA132 ) ;
  
  tfloat sinA123 = Sin( A123 ) ;
  
  tfloat sin_alpha12 = Sin( alpha12 ) ;
  tfloat sin_alpha13 = Sin( alpha13 ) ;
  tfloat cos_alpha13 = Cos( alpha13 ) ;
  
  /* valid for topology 1, I haven't implemented the second one */
  tfloat Ap12 = - atan( (L23*sin_alpha12*(sin_alpha13*cosA123 - cos_alpha13*sinA123)) / (L12*Sin(alpha23) + L23*sin_alpha12*(cos_alpha13*cosA123 + sin_alpha13*sinA123) ) ) ;
  tfloat A23p = A123 - Ap12 - alpha13 ;
  
  tfloat tau = atan2( (y3-y1) , (x3-x1) ) ;
  tfloat cos_tau = Cos( tau ) ;
  tfloat sin_tau = Sin( tau ) ;
  
  tfloat T1 = Tan( A23p + A132 ) ;
  tfloat T2 = Tan( Ap12 + A213 ) ;
    
  tfloat x_ = L13 * T1 / ( T2 + T1 ) ;
  tfloat y_ = (x_) * T2 ;
  
  *x = x_ * cos_tau - y_ * sin_tau + x1 ;
  *y = x_ * sin_tau + y_ * cos_tau + y1 ;
  
  return tau;
}

