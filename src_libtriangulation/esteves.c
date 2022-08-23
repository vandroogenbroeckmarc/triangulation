/**
 * @file esteves.c 
 * @date 18/03/2011
 * @author Vincent Pierlot
 * 
 *  The algorithm was implemented after \cite Esteves2006Position.
*/
#include  <math.h>
#include  "const.h"
#include  "esteves.h"

tfloat triangulationEsteves(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ;
  if( alpha1 > alpha2 ) alpha12 += TWOPI ;
  
  tfloat alpha31 = alpha1 - alpha3 ;
  if( alpha3 > alpha1 ) alpha31 += TWOPI ;
  
  tfloat L12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat L31 = sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) ) ;
  
  tfloat phi = atan2( (y1-y2) , (x1-x2) ) ; /* not given in the paper */
  tfloat sigma = atan2( (x1-x3) , (y1-y3) ) + HALFPI + phi ; /* not given in the paper */
  
  tfloat gamma = sigma - alpha31 ;
  
  tfloat sin_alpha12 = Sin( alpha12 ) ;
  tfloat sin_alpha31 = Sin( alpha31 ) ;
  
  tfloat tau = atan( (sin_alpha12*(L12*sin_alpha31 - L31*Sin(gamma))) / (L31*sin_alpha12*Cos(gamma) - L12*Cos(alpha12)*sin_alpha31) ) ;
  
  if( (alpha12 < PI) && (tau < 0.0) ) tau += PI ;
  if( (alpha12 > PI) && (tau > 0.0) ) tau -= PI ;
  
  if(tau == 0.0)
    if( ( (sigma > 0.0) && (alpha31 > PI) ) || ( (sigma < 0.0) && (alpha31 < PI) ) ) tau = PI ;
    
  tfloat L1;
  if( fabs( sin_alpha12 ) > fabs( sin_alpha31 ) )
    L1 = ( L12 * Sin( tau + alpha12 ) ) / sin_alpha12 ;
  else
    L1 = ( L31 * Sin( tau + sigma - alpha31 ) ) / sin_alpha31 ;
    
  *x = x1 - L1 * Cos( phi + tau ) ;
  *y = y1 - L1 * Sin( phi + tau ) ;
  
  return tau;
}

