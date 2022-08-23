/**
 * @file mcgillem.c 
 * @date 04/09/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Mcgillem1989ABeacon.
*/
#include  <math.h>
#include  "const.h"
#include  "mcgillem.h"

tfloat triangulationMcGillemTrigo(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat phi1 = alpha1 - alpha2 ;
  tfloat phi2 = alpha2 - alpha3 ;
  
  tfloat sin_phi1 = Sin( phi1 ) ;
  tfloat sin_phi2 = Sin( phi2 ) ;
  
  tfloat Phi1 = HALFPI - atan2( (y2-y1) , (x2-x1) ) ;
  tfloat Phi2 = HALFPI - atan2( (y3-y2) , (x3-x2) ) ;
  
  tfloat w = QUARTPI + atan( ( d12 * sin_phi2 ) / ( d23 * sin_phi1 ) ) ;
  
  tfloat v = HALFPI - ( Phi1 - Phi2 + phi1 + phi2 ) / 2 ;
  
  tfloat gamma = v + atan( tan(v) / tan(w) ) ;
  
  tfloat dAP = d12 * Sin( gamma + phi1 ) / sin_phi1 ;
  
  *x = x1 + dAP * Sin( Phi1 + gamma ) ;
  *y = y1 + dAP * Cos( Phi1 + gamma ) ;
  
  return 0;
}

tfloat triangulationMcGillemGeometric(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat phi1 = alpha1 - alpha2 ;
  tfloat phi2 = alpha2 - alpha3 ;
  
  tfloat sigma1 = -atan2( (y2-y1) , (x2-x1) ) ;
  tfloat sigma2 = -atan2( (y3-y2) , (x3-x2) ) ;
  
  tfloat R1 = d12 / ( 2 * Sin( phi1 ) ) ;
  tfloat R2 = d23 / ( 2 * Sin( phi2 ) ) ;
  
  tfloat xn = x1 - R1 * Sin( sigma1 - phi1 ) ;
  tfloat yn = y1 - R1 * Cos( sigma1 - phi1 ) ;
  
  tfloat xm = x2 - R2 * Sin( sigma2 - phi2 ) ;
  tfloat ym = y2 - R2 * Cos( sigma2 - phi2 ) ;
  
  tfloat m = ( ym - yn ) / ( xn - xm ) ;
  tfloat n = ( R2*R2 - R1*R1 - xm*xm + xn*xn - ym*ym + yn*yn ) / ( 2*( xn - xm ) ) ;
  
  *y = ( ( 2*m*xn + 2*yn - 2*m*n ) / ( 1 + m*m ) ) - y2 ;
  *x = m * (*y) + n ;
  
  return n;
}

