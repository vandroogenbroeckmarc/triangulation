/**
 * @file total.c
 * @brief Implementation of the ToTal algorithm   
 * @date 15/02/2011
 *  The algorithm was implemented after \cite Pierlot2014ANewThree (published earlier in \cite Pierlot2011ANewThreeObject ). This algorithm was used develop in the context of the Eurobot contest. 

 * @author Vincent Pierlot
*/
#include  <math.h>
#include  "const.h"
#include  "total.h"

/*
 * Version with mathematical approximation of the limit for the pseudosingularities
*/
tfloat triangulationPierlot(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
	tfloat cot_12 = Cot( alpha2 - alpha1 ) ;
	tfloat cot_23 = Cot( alpha3 - alpha2 ) ;
	cot_12 = adjust_value_to_bounds( cot_12 , COT_MAX ) ;
	cot_23 = adjust_value_to_bounds( cot_23 , COT_MAX ) ;
	tfloat cot_31 = ( 1.0 - cot_12 * cot_23 ) / ( cot_12 + cot_23 ) ;
	cot_31 = adjust_value_to_bounds( cot_31 , COT_MAX ) ;
	
	tfloat x1_ = x1 - x2 , y1_ = y1 - y2 , x3_ = x3 - x2 , y3_ = y3 - y2 ;

	tfloat c12x = x1_ + cot_12 * y1_ ;
	tfloat c12y = y1_ - cot_12 * x1_ ;

	tfloat c23x = x3_ - cot_23 * y3_ ;
	tfloat c23y = y3_ + cot_23 * x3_ ;

	tfloat c31x = (x3_ + x1_) + cot_31 * (y3_ - y1_) ;
	tfloat c31y = (y3_ + y1_) - cot_31 * (x3_ - x1_) ;
	tfloat k31 = (x3_ * x1_) + (y3_ * y1_) + cot_31 * ( (y3_ * x1_) - (x3_ * y1_) ) ;
  
  tfloat D = (c12x - c23x) * (c23y - c31y) - (c23x - c31x) * (c12y - c23y) ;
  tfloat invD = 1.0 / D ;
  tfloat K = k31 * invD ;
  
	*x = K * (c12y - c23y) + x2 ;
	*y = K * (c23x - c12x) + y2 ;
	
	return invD ; /* return 1/D */
}

/*
 * Version with exact limits for the pseudosingularities (3 cases)
*/
tfloat triangulationPierlot2(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
						tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  tfloat alpha_12 = alpha2 - alpha1 ;
  tfloat alpha_23 = alpha3 - alpha2 ;
  tfloat alpha_31 = alpha1 - alpha3 ;
  
	tfloat x1_ , y1_ , x2_ , y2_ , x3_ , y3_ ;
	
	tfloat cot_12 , cot_23 , cot_31 , c12x , c12y , c23x , c23y , c31x , c31y , k , D , invD , K ;
  
  if ( alpha_12 == PI || alpha_12 == 0.0 )
  {
    x1_ = x1 - x3 , y1_ = y1 - y3 , x2_ = x2 - x3 , y2_ = y2 - y3 ;
    
    cot_23 = cot( alpha_23 ) ;
    
    c12x = (y1_ - y2_) ;
    c12y = (x2_ - x1_) ;
    k = (y1_ * x2_) - (x1_ * y2_) ;
	  
	  c23x = x2_ + cot_23 * y2_ ;
	  c23y = y2_ - cot_23 * x2_ ;

	  c31x = x1_ + cot_23 * y1_ ;
	  c31y = y1_ - cot_23 * x1_ ;
  
    D = (c31x - c23x) * (c12y) + (c12x) * (c23y - c31y) ;
    invD = 1.0 / D ;
    K = k * invD ;
  
	  *x = K * ( c23y - c31y ) + x3 ;
	  *y = K * ( c31x - c23x ) + y3 ;
	
	  return invD ;
  }
  
  if ( alpha_23 == PI || alpha_23 == 0.0 )
  {
    x2_ = x2 - x1 , y2_ = y2 - y1 , x3_ = x3 - x1 , y3_ = y3 - y1 ;
    
    cot_31 = cot( alpha_31 ) ;
    
	  c12x = x2_ + cot_31 * y2_ ;
	  c12y = y2_ - cot_31 * x2_ ;
	  
	  c23x = (y2_ - y3_) ;
	  c23y = (x3_ - x2_) ;
	  k = (y2_ * x3_) - (x2_ * y3_) ;

	  c31x = x3_ + cot_31 * y3_ ;
	  c31y = y3_ - cot_31 * x3_ ;
  
    D = (c12x - c31x) * (c23y) + (c23x) * (c31y - c12y) ;
    invD = 1.0 / D ;
    K = k * invD ;
  
	  *x = K * ( c31y - c12y ) + x1 ;
	  *y = K * ( c12x - c31x ) + y1 ;
	
	  return invD ;
  }
  
  if ( alpha_31 == PI || alpha_31 == 0.0 )
  {
    x1_ = x1 - x2 , y1_ = y1 - y2 , x3_ = x3 - x2 , y3_ = y3 - y2 ;
    
    cot_12 = cot( alpha_12 ) ;
    
	  c12x = x1_ + cot_12 * y1_ ;
	  c12y = y1_ - cot_12 * x1_ ;
	  
	  c23x = x3_ + cot_12 * y3_ ;
	  c23y = y3_ - cot_12 * x3_ ;

	  c31x = (y3_ - y1_) ;
	  c31y = (x1_ - x3_) ;
	  k = (y3_ * x1_) - (x3_ * y1_) ;
  
    D = (c23x - c12x) * (c31y) + (c31x) * (c12y - c23y) ;
    invD = 1.0 / D ;
    K = k * invD ;
  
	  *x = K * (c12y - c23y) + x2 ;
	  *y = K * (c23x - c12x) + y2 ;
	
	  return invD ;
  }
  
  x1_ = x1 - x2 , y1_ = y1 - y2 , x3_ = x3 - x2 , y3_ = y3 - y2 ;
  
	cot_12 = cot( alpha_12 ) ;
	cot_23 = cot( alpha_23 ) ;
	cot_31 = ( 1.0 - cot_12*cot_23 ) / (cot_12 + cot_23) ;
	
	c12x = x1_ + cot_12 * y1_ ;
	c12y = y1_ - cot_12 * x1_ ;

	c23x = x3_ - cot_23 * y3_ ;
	c23y = y3_ + cot_23 * x3_ ;

	c31x = (x3_ + x1_) + cot_31 * (y3_ - y1_) ;
	c31y = (y3_ + y1_) - cot_31 * (x3_ - x1_) ;
	k = (x3_ * x1_) + (y3_ * y1_) + cot_31 * ( (y3_ * x1_) - (x3_ * y1_) ) ;
  
  D = (c12x - c23x) * (c23y - c31y) - (c23x - c31x) * (c12y - c23y) ;
  invD = 1.0 / D ;
  K = k * invD ;
  
	*x = K * (c12y - c23y) + x2 ;
	*y = K * (c23x - c12x) + y2 ;
	
	return invD ; /* return 1/D */
}

