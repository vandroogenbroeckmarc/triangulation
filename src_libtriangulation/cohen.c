/**
 * @file cohen.c 
 * @date 28/08/2012
 * @author Vincent Pierlot

 *  The algorithm was implemented after \cite Esteves2003Generalized (same as \cite Cohen1992AComprehensive).
 *  Unlike what is written in the paper, this method seems to work in all cases and beacon configurations.
 *  Maybe it is due to the use of atan2() since it is not mentioned in the paper.
*/
#include  <math.h>
#include  "const.h"
#include  "cohen.h"

/* Trigonometric version */
tfloat triangulationCohenTrigo(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ;
  tfloat alpha31 = alpha1 - alpha3 ;
  
  tfloat L12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat L31 = sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) ) ;
  
  tfloat phi = atan2( (y1-y2) , (x1-x2) ) ;
  tfloat sigma = atan2( (x1-x3) , (y1-y3) ) + HALFPI + phi ; /* different from the paper */
  
  tfloat gamma = sigma - alpha31 ;
  
  tfloat sin_alpha12 = Sin( alpha12 ) ;
  tfloat sin_alpha31 = Sin( alpha31 ) ;
  
  tfloat p = ( L31 * sin_alpha12 ) / ( L12 * sin_alpha31 ) ;
  tfloat tau = atan( ( sin_alpha12 - p * Sin( gamma ) ) / ( p * Cos( gamma ) - Cos( alpha12 ) ) ) ;
    
  tfloat L1 = ( L12 * Sin( tau + alpha12 ) ) / sin_alpha12 ;
    
  *x = x1 - L1 * Cos( phi + tau ) ;
  *y = y1 - L1 * Sin( phi + tau ) ;
  
  return tau;
}

/*
Note: Cohen 2 = Kortenkamp
*/

/* Geometric Circle Intersection version */
tfloat triangulationCohenGeometricOriginal(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ; /* alpha */
  tfloat alpha23 = alpha3 - alpha2 ; /* beta */
  
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat ra = d12 / ( 2 * Sin( alpha12 ) ) ;
  tfloat rb = d23 / ( 2 * Sin( alpha23 ) ) ;
  
  tfloat la = d12 / ( 2 * adjust_value_to_bounds( Tan( alpha12 ) , COT_MAX ) ) ;
  tfloat lb = d23 / ( 2 * adjust_value_to_bounds( Tan( alpha23 ) , COT_MAX ) ) ;
  
  tfloat cax = ( x1 + x2 ) / 2 - la * ( y2 - y1 ) / d12 ;
  tfloat cay = ( y1 + y2 ) / 2 + la * ( x2 - x1 ) / d12 ;
  
  tfloat cbx = ( x2 + x3 ) / 2 - lb * ( y3 - y2 ) / d23 ;
  tfloat cby = ( y2 + y3 ) / 2 + lb * ( x3 - x2 ) / d23 ;
  
  tfloat d = sqrt( (cbx-cax)*(cbx-cax) + (cby-cay)*(cby-cay) ) ;
  
  tfloat c2m = ( rb*rb + d*d - ra*ra ) / ( 2 * d ) ; /* different from the paper; taken from Casanova */
  
  /*tfloat phi = atan2( (cay-cby) , (cax-cbx) ) ;
  tfloat mx = cbx + c2m * cos(phi) ; printf("mx = %f\n", mx);
  tfloat my = cby + c2m * sin(phi) ; printf("my = %f\n", my);*/
  
  tfloat mx = cbx + c2m * ( cax - cbx ) / d ; /* optimized */
  tfloat my = cby + c2m * ( cay - cby ) / d ; /* optimized */
  
  *x = 2 * mx - x2 ;
  *y = 2 * my - y2 ;
  
  return d;
}

tfloat triangulationCohenGeometric(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha12 = alpha2 - alpha1 ; /* alpha */
  tfloat alpha23 = alpha3 - alpha2 ; /* beta */
  
  tfloat d12 = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) ;
  tfloat d23 = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) ) ;
  
  tfloat ra = d12 / ( Sin( alpha12 ) ) ; /* x2 */
  tfloat rb = d23 / ( Sin( alpha23 ) ) ; /* x2 */
  
  tfloat la = adjust_value_to_bounds( Cot( alpha12 ) , COT_MAX ) ; /* optimized */
  tfloat lb = adjust_value_to_bounds( Cot( alpha23 ) , COT_MAX ) ; /* optimized */
  
  tfloat cax = ( x1 + x2 ) - la * ( y2 - y1 ) ; /* optimized */ /* x2 */
  tfloat cay = ( y1 + y2 ) + la * ( x2 - x1 ) ; /* optimized */ /* x2 */
  
  tfloat cbx = ( x2 + x3 ) - lb * ( y3 - y2 ) ; /* optimized */ /* x2 */
  tfloat cby = ( y2 + y3 ) + lb * ( x3 - x2 ) ; /* optimized */ /* x2 */
  
  tfloat d = (cbx-cax)*(cbx-cax) + (cby-cay)*(cby-cay) ; /* x4 */
  
  tfloat c2m = ( rb*rb + d - ra*ra ) / ( 2 * d ) ; /* different from the paper; taken from Casanova */ /* unchanged */
  
  *x = cbx + c2m * ( cax - cbx ) - x2 ; /* optimized */
  *y = cby + c2m * ( cay - cby ) - y2 ; /* optimized */
  
  return d;
}

