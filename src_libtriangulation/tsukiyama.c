/**
 * @file tsukiyama.c 
 * @date 05/09/2012
 * @author Vincent Pierlot
 *
 *  The algorithm was implemented after \cite Tsukiyama2009Mobile.
 *  IT DOES NOT WORK IN MOST OF THE CASES. SOMETIMES THE SOLUTION IS BEACON 2 LOCATION. SEE SECOND ALGORITHM.
*/
#include  <math.h>
#include  "const.h"
#include  "tsukiyama.h"

tfloat triangulationTsukiyamaOriginal(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat phi1 = alpha1 - alpha2 ;
  tfloat phi2 = alpha2 - alpha3 ;
  
  tfloat gamma1 = atan2( (y2-y1) , (x2-x1) ) ;
  tfloat gamma2 = atan2( (y3-y2) , (x3-x2) ) ;
  
  tfloat R1 = d12 / ( 2 * Sin( phi1 ) ) ;
  tfloat R2 = d23 / ( 2 * Sin( phi2 ) ) ;
  
  tfloat theta1 = acos( d12 / ( 2 * R1 ) ) ;
  tfloat theta2 = acos( d23 / ( 2 * R2 ) ) ;
  
  tfloat cx1 = x1 + R1 * Cos( gamma1 - theta1 ) ;
  tfloat cy1 = y1 + R1 * Sin( gamma1 - theta1 ) ;
  
  tfloat cx2 = x2 + R2 * Cos( gamma2 - theta2 ) ;
  tfloat cy2 = y2 + R2 * Sin( gamma2 - theta2 ) ;
  
  tfloat d = sqrt( (cx2-cx1)*(cx2-cx1) + (cy2-cy1)*(cy2-cy1) ) ;
  
  tfloat phi = acos( ( R1 * R1 + d * d - R2 * R2 ) / ( 2 * R1 * d ) ) ;
  tfloat sigma = atan2( ( cy2 - cy1 ) , ( cx2 - cx1 ) ) ;
  
  *x = cx1 + R1 * Cos( phi - sigma ) ;
  *y = cy1 - R1 * Sin( phi - sigma ) ; /* in the paper, it's an addition... */
  
  return d;
}

/*
 *  Created by Vincent Pierlot on 05/09/2012.
 *  The algorithm was implemented after Tsukiyama2009Mobile.
 *  Actually, the algorithm is a little bit different because the paper version didn't work. See comments below.
*/
tfloat triangulationTsukiyama(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat phi1 = alpha1 - alpha2 ;
  tfloat phi2 = alpha2 - alpha3 ;
  
  tfloat gamma1 = atan2( (y2-y1) , (x2-x1) ) ;
  tfloat gamma2 = atan2( (y3-y2) , (x3-x2) ) ;
  
  tfloat R1 = d12 / ( 2 * Sin( phi1 ) ) ;
  tfloat R2 = d23 / ( 2 * Sin( phi2 ) ) ;
  
  tfloat cx1 = x1 + R1 * Sin( gamma1 + phi1 ) ; /* changed from the paper since theta1 = PI/2 - phi1 */
  tfloat cy1 = y1 - R1 * Cos( gamma1 + phi1 ) ; /* changed from the paper since theta1 = PI/2 - phi1 */
  
  tfloat cx2 = x2 + R2 * Sin( gamma2 + phi2 ) ; /* changed from the paper since theta2 = PI/2 - phi2 */
  tfloat cy2 = y2 - R2 * Cos( gamma2 + phi2 ) ; /* changed from the paper since theta2 = PI/2 - phi2 */
  
  tfloat d = sqrt( (cx2-cx1)*(cx2-cx1) + (cy2-cy1)*(cy2-cy1) ) ;
  
  tfloat phi = acos( ( R1*R1 + d*d - R2*R2 ) / ( 2 * R1 * d ) ) ;
  tfloat sigma = atan2( ( cy2 - cy1 ) , ( cx2 - cx1 ) ) ;
  
  /* compute the two possible solutions, like Casanova, and choose the solution that is not beacon 2 location */
  tfloat R1x = cx1 + R1 * Cos( phi - sigma ) ;
  tfloat R1y = cy1 - R1 * Sin( phi - sigma ) ;
  tfloat v1 = sqrt( (R1x-x2)*(R1x-x2) + (R1y-y2)*(R1y-y2) ) ;
  
  tfloat R2x = cx1 + R1 * Cos( phi + sigma ) ;
  tfloat R2y = cy1 + R1 * Sin( phi + sigma ) ;
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

