/**
 * @file fontllagunes.c 
 * @date 18/03/2011
 * @author Vincent Pierlot
 *
 *  The first algorithm was implemented after \cite Font-Llagunes2009Consistent.
 *  The second algorithm was implemented after \cite Font-Llagunes2009New.
*/
#include  <math.h>
#include  "const.h"
#include  "fontllagunes.h"

tfloat triangulationFontLlagunes(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat cot_alpha = Cot( alpha2 - alpha1 ) ;
  tfloat cot_beta =  Cot( alpha3 - alpha2 ) ;
  cot_alpha = adjust_value_to_bounds( cot_alpha , COT_MAX ) ;
  cot_beta =  adjust_value_to_bounds( cot_beta , COT_MAX ) ;
  
  tfloat phi = atan2( (y3-y2) , (x3-x2) ) ;
  tfloat sin_phi = Sin(phi) ;
  tfloat cos_phi = Cos(phi) ;
  
  tfloat x3r =  cos_phi * ( x3 - x2 ) + sin_phi * ( y3 - y2 ) ;
  tfloat x1r =  cos_phi * ( x1 - x2 ) + sin_phi * ( y1 - y2 ) ;
  tfloat y1r = -sin_phi * ( x1 - x2 ) + cos_phi * ( y1 - y2 ) ;
  
  tfloat eta = ( x3r - x1r - y1r*cot_alpha ) / ( x3r*cot_beta - y1r + x1r*cot_alpha ) ;
  
  tfloat k = ( 1 - eta*cot_beta ) / ( 1 + eta*eta ) ;
  
  tfloat xr = x3r * k ;
  tfloat yr = xr * (-eta) ;
  
  *x = x2 + cos_phi * xr - sin_phi * yr ;
  *y = y2 + sin_phi * xr + cos_phi * yr ;
  
  return eta ;
}

/* TODO: handle singularities correctly */
tfloat triangulationFontLlagunes2(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
	tfloat theta = 0.0 ; /* first guess */
	
  tfloat alpha12 = alpha2 - alpha1 ; /* alpha */
  tfloat alpha23 = alpha3 - alpha2 ; /* beta */
	
	tfloat mA = Cot( theta ) ;
	tfloat mB = Cot( theta - alpha12 ) ;
	tfloat mC = Cot( theta - alpha12 - alpha23 ) ;
	mA = adjust_value_to_bounds( mA , COT_MAX ) ;
	mB = adjust_value_to_bounds( mB , COT_MAX ) ;
	mC = adjust_value_to_bounds( mC , COT_MAX ) ;
	
	tfloat xPAB = ( mA * x1 - mB * x2 - y1 + y2 ) / ( mA - mB ) ;
	tfloat yPAB = mA * ( xPAB - x1 ) + y1 ;
	tfloat xPBC = ( mB * x2 - mC * x3 - y2 + y3 ) / ( mB - mC ) ;
	tfloat yPBC = mB * ( xPBC - x2 ) + y2 ;
	tfloat xPAC = ( mA * x1 - mC * x3 - y1 + y3 ) / ( mA - mC ) ;
	tfloat yPAC = mA * ( xPAC - x1 ) + y1 ;
	
	tfloat Ap = ( ( xPAB - xPBC ) * ( yPBC - yPAC ) - ( xPBC - xPAC ) * ( yPAB - yPBC ) )/* / 2*/ ;
	Ap = ( Ap < 0.0 ) ? -Ap : Ap ;
  
	tfloat cot_12 = Cot( alpha12 ) ;
	tfloat cot_23 = Cot( alpha23 ) ;
	tfloat cot_31 = ( 1.0 - cot_12 * cot_23 ) / ( cot_12 + cot_23 ) ; /* optimization like ToTal */
	cot_12 = adjust_value_to_bounds( cot_12 , COT_MAX ) ;
	cot_23 = adjust_value_to_bounds( cot_23 , COT_MAX ) ;
	cot_31 = adjust_value_to_bounds( cot_31 , COT_MAX ) ;

	tfloat xCAB = ( x1 + x2 + ( y1 - y2 ) * cot_12 )/* / 2*/ ;
	tfloat yCAB = ( y1 + y2 + ( x2 - x1 ) * cot_12 )/* / 2*/ ;
	tfloat xCBC = ( x2 + x3 + ( y2 - y3 ) * cot_23 )/* / 2*/ ;
	tfloat yCBC = ( y2 + y3 + ( x3 - x2 ) * cot_23 )/* / 2*/ ;
	tfloat xCAC = ( x1 + x3 - ( y1 - y3 ) * cot_31 )/* / 2*/ ;
	tfloat yCAC = ( y1 + y3 - ( x3 - x1 ) * cot_31 )/* / 2*/ ;
	
	tfloat Ac = ( ( xCAB - xCBC ) * ( yCBC - yCAC ) - ( xCBC - xCAC ) * ( yCAB - yCBC ) )/* / 2*/ ;
	Ac = ( Ac < 0.0 ) ? -Ac : Ac ;
	
	tfloat delta_theta = asin( sqrt( Ap / Ac )/* / 2*/ ) ;
	delta_theta = ( delta_theta < 0.0 ) ? -delta_theta : delta_theta ;
	
	tfloat S = ( xPBC - xPAB ) * ( yCBC - yCAB ) - ( xCBC - xCAB ) * ( yPBC - yPAB ) ;
	if ( S < 0.0 ) delta_theta = -delta_theta ;
	
	theta += delta_theta ;
	
	mA = Cot( theta ) ;
	mB = Cot( theta - alpha12 ) ;
	mA = adjust_value_to_bounds( mA , COT_MAX ) ;
	mB = adjust_value_to_bounds( mB , COT_MAX ) ;
  
	*x = ( mA * x1 - mB * x2 - y1 + y2 ) / ( mA - mB ) ;
	*y = mA * ( (*x) - x1 ) + y1 ;
	
	return Ac ;
}
