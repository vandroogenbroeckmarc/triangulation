/**
 * @file zalama.c 
 * @date 03/09/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Casanova2002ANewBeacon.
 *  Actually, the algorithm is a little bit different because the paper version didn't work. See comments below.
*/
#include  <math.h>
#include  "const.h"
#include  "zalama.h"

tfloat triangulationZalama(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ;
  tfloat alpha23 = alpha3 - alpha2 ;
  
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat delta12 = atan2( (y2-y1) , (x2-x1) ) ;
  tfloat ra = d12 / ( 2 * Sin( alpha12 ) ) ;
  tfloat cax = x1 - ra * Sin( delta12 - alpha12 ) ;
  tfloat cay = y1 + ra * Cos( delta12 - alpha12 ) ;
  
  tfloat delta23 = atan2( (y3-y2) , (x3-x2) ) ;
  tfloat rb = d23 / ( 2 * Sin( alpha23 ) ) ;
  tfloat cbx = x2 - rb * Sin( delta23 - alpha23 ) ;
  tfloat cby = y2 + rb * Cos( delta23 - alpha23 ) ;
  
  tfloat d = sqrt( (cbx-cax)*(cbx-cax) + (cby-cay)*(cby-cay) ) ;
  
  tfloat d2r = ( rb*rb + d*d - ra*ra ) / ( 2 * d ) ;
  
  tfloat gamma = acos( d2r / rb ) ;
  
  tfloat phi = atan2( (cay-cby) , (cax-cbx) ) ;
  
  tfloat R1x = cbx + rb * Cos( gamma - phi ) ; /* the paper uses 'cax' and 'ra' */
  tfloat R1y = cby - rb * sin( gamma - phi ) ; /* the paper uses 'cay' and 'ra' */
  tfloat v1 = sqrt( (R1x-x2)*(R1x-x2) + (R1y-y2)*(R1y-y2) ) ;
  
  tfloat R2x = cbx + rb * Cos( phi + gamma ) ; /* the paper uses 'cax' and 'ra' */
  tfloat R2y = cby + rb * Sin( phi + gamma ) ; /* the paper uses 'cay' and 'ra' */
  tfloat v2 = sqrt( (R2x-x2)*(R2x-x2) + (R2y-y2)*(R2y-y2) ) ;
  
  if( v1 > v2 )
  {
    *x = R1x ;
    *y = R1y ;
  }
  else
  {
    *x = R2x ;
    *y = R2y ;
  }
  
  return d;
}

