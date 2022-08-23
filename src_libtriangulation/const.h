/**
 * @file const.h
 * @author Vincent Pierlot
 *
*/
#ifndef __CONST_H__
#define __CONST_H__

/** \def PI
    \brief The value of PI
 */
#define PI          3.141592654
#define TWOPI       6.283185307
#define FOURPI      12.566370614
#define HALFPI      1.570796327
#define QUARTPI     0.785398163
#define INVQUARTPI  1.273239545
#define INVTWOPI    0.159154943

#define RAD2DEG     (180/PI)
#define DEG2RAD     (PI/180)
#define COT_MAX     100000000

#define cot(x)      ( 1 / tan(x) )

#define abs(x)      ( ( x < 0 ) ? -x : x )

#define adjust_value_to_bounds( value , max )  ( ( value > max ) ? max : ( ( value < -max ) ? -max : value ) )  

#define Sin(x)  sin(x)
#define Cos(x)  cos(x)
#define Cot(x)  cot(x)
#define Tan(x)  tan(x)

/** \var typedef tfloat    
    \brief Defines the type for float/double  
 */
typedef double      tfloat ;

#endif

