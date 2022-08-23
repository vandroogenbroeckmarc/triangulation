/**
 * @file toolbox.c
 * @brief ...
 * @author Vincent Pierlot
*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <sys/time.h>
#include  "const.h"
#include  "toolbox.h"
#include  "methods.h"

#ifdef _WIN32
long int random(void) { return (long int) rand(); }
void srandom(unsigned int seed) { srand(seed); }
#endif

/**
* @brief 
*
* @param in
* @param out
* @param width
* @param height
* @param numgraylevels
*/
static void map_to_grayscale_hist ( tfloat * in , tfloat * out , unsigned int width , unsigned int height , unsigned int numgraylevels );

/**
* @brief 
*
* @param in
* @param out
* @param width
* @param height
* @param p
*/
static void map_to_grayscale_sat ( tfloat * in , tfloat * out , unsigned int width , unsigned int height , unsigned int p );

/**
* @brief 
*
* @param in
* @param out
* @param scale
* @param width
* @param height
* @param numgraylevels
*/
static void map_to_grayscale_lin ( tfloat * in , tfloat * out , tfloat * scale , unsigned int width , unsigned int height , unsigned int numgraylevels );

/**
* @brief 
*
* @param in
* @param out
* @param scale
* @param width
* @param height
* @param numgraylevels
* @param P1
*/
static void map_to_grayscale_log ( tfloat * in , tfloat * out , tfloat * scale , unsigned int width , unsigned int height , unsigned int numgraylevels , tfloat P1 );


/**
* Computes the angles (a1,a2,a3) measured by a robot (xr,yr) from beacons (x1,y1), (x2,y2), (x3,y3).
* The orientation of the robot is given by 'or', and angles are computed relatively to 'or'.
*
* @param a1
* @param a2
* @param a3
* @param xr
* @param yr
* @param or
* @param x1
* @param y1
* @param x2
* @param y2
* @param x3
* @param y3
*/
void get_angles(tfloat *a1, tfloat *a2, tfloat *a3, tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
  *a1 = atan2( (y1 - yr) , (x1 - xr) ) - or ;
  *a2 = atan2( (y2 - yr) , (x2 - xr) ) - or ;
  *a3 = atan2( (y3 - yr) , (x3 - xr) ) - or ;
}

/**
*  Triangulates robot position (x,y) from measured angles alpha1, alpha2, and alpha3,
*  and beacons locations (x1,y1), (x2,y2), and (x3,y3).
*  Uses triangulation method 'm' given in command line.
*
* @param x
* @param y
* @param alpha1
* @param alpha2
* @param alpha3
* @param x1
* @param y1
* @param x2
* @param y2
* @param x3
* @param y3
* @param method
*
* @return 
*/
tfloat triangulationMethod(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
					  tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int method)
{
  switch( method )
  {
    case 1:  return triangulationPierlot(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 2:  return triangulationEsteves(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 3:  return triangulationFontLlagunes(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 4:  return triangulationZalama(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 5:  return triangulationMcGillemTrigo(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 6:  return triangulationMcGillemGeometric(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 7:  return triangulationEaston(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 8:  return triangulationHmam(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 9:  return triangulationCohenTrigo(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 10: return triangulationCohenGeometric(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 11: return triangulationCohenGeometricOriginal(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 12: return triangulationTsukiyama(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 13: return triangulationTsukiyamaOriginal(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 14: return triangulationMadsen(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 15: return triangulationLukic(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 16: return triangulationLukicOriginal(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 17: return triangulationTienstra(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 18: return triangulationLigas(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 19: return triangulationFontLlagunes2(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 20: return triangulationKaestner(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 21: return triangulationCollins(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 22: return triangulationCassini(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    case 42: return triangulationPierlot2(x, y, alpha1, alpha2, alpha3, x1, y1, x2, y2, x3, y3) ;
    default: fprintf(stderr, "triangulationMethod(): Bad method number!\n") ; return -1 ;
  }
}

/**
* @brief Computes the algebraic mean of the array data[] of length N.
*
* @param data[]
* @param N
*
* @return 
*/
tfloat mean( tfloat data[] , unsigned long N )
{
  unsigned long i ;
  tfloat mean = 0.0 ;
  
  for( i = 0 ; i < N ; ++i )
    mean += data[i] ;
  mean /= N ;
  
  return mean ;
}

/**
* @brief Computes the variance of the array data[] of length N.
*
* @param data[]
* @param N
*
* @return 
*/
tfloat variance( tfloat data[] , unsigned long N )
{
  unsigned long i ;
  tfloat m = 0.0 , variance = 0.0 ;
  
  m = mean( data , N ) ;
  
  for( i = 0 ; i < N ; ++i )
    variance += (data[i]-m) * (data[i]-m) ;
  variance /= N ;
  
  return variance ;
}

/**
* @brief  Initializes the random number generator with current time.
*/
void initRand()
{
	struct timeval startTime ;
	gettimeofday( &startTime , NULL ) ;
	srandom( startTime.tv_usec ) ;
}

/**
*  Returns an occurence of a normally distributed random variable.
*  Uses the Marsaglia polar method (polar version of Box-Muller transform).
*  http://en.wikipedia.org/wiki/Box_Muller_transform
*
* @return 
*/
tfloat gaussianRand()
{
  tfloat u , v , s = 0.0 ;
  
  while( s == 0.0 || s >= 1.0 )
  {
    u = ( ( (tfloat) random() / (tfloat) RAND_MAX ) * 2.0 ) - 1.0 ;
    v = ( ( (tfloat) random() / (tfloat) RAND_MAX ) * 2.0 ) - 1.0 ;
    s = u*u + v*v ;
  }
  
  return u * sqrt( -2 * log(s) / s ) ;
}


/**
*  Simulates the beacon position sensitivity of the triangulation method 'm', for measured angles alpha1, alpha2, and alpha3,
*  and beacons locations (x1,y1), (x2,y2), and (x3,y3).
*  'sigma' is the standard deviation of beacon coordinates.
*  The simulation is performed 'n' times.
*
* @param xTrue
* @param yTrue
* @param x1
* @param y1
* @param x2
* @param y2
* @param x3
* @param y3
* @param method
* @param sigmaAngle
* @param sigmaBeacon
* @param n
* @param outputType
* @param thresh
*
* @return 
*/
tfloat triangulationSensitivity(tfloat xTrue, tfloat yTrue, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3,
					                      int method, tfloat sigmaAngle, tfloat sigmaBeacon, unsigned int n, int outputType, double thresh)
{
  tfloat alpha1 ;
	tfloat alpha2 ;
	tfloat alpha3 ;
	tfloat oTrue = 0.0 ;
  tfloat xNoise = 0.0 ;
	tfloat yNoise = 0.0 ;
	tfloat oNoise = 0.0 ;
	tfloat qual = 0.0 ;
	
	tfloat ea1=0.0, ea2=0.0, ea3=0.0, ex1=0.0, ey1=0.0, ex2=0.0, ey2=0.0, ex3=0.0, ey3=0.0, s ;
	tfloat *errP = ( tfloat * ) malloc( n * sizeof(tfloat) ) ; if( errP == NULL ) return -1 ;
	tfloat *errO = ( tfloat * ) malloc( n * sizeof(tfloat) ) ; if( errO == NULL ) return -1 ;
	tfloat *Qual = ( tfloat * ) malloc( n * sizeof(tfloat) ) ; if( Qual == NULL ) return -1 ;
	
	int i ;
	
  initRand() ;
	
	for ( i = 0 ; i < n ; ++i )
	{
	  if ( sigmaAngle != 0.0 )
	  {
	    ea1 = gaussianRand() * sigmaAngle ;
	    ea2 = gaussianRand() * sigmaAngle ;
	    ea3 = gaussianRand() * sigmaAngle ;
	  }
	  if ( sigmaBeacon != 0.0 )
	  {
	    ex1 = gaussianRand() * sigmaBeacon ;
	    ey1 = gaussianRand() * sigmaBeacon ;
	    ex2 = gaussianRand() * sigmaBeacon ;
	    ey2 = gaussianRand() * sigmaBeacon ;
	    ex3 = gaussianRand() * sigmaBeacon ;
	    ey3 = gaussianRand() * sigmaBeacon ;
	  }
	  
	  get_angles(&alpha1, &alpha2, &alpha3, xTrue, yTrue, 0.0, x1+ex1, y1+ey1, x2+ex2, y2+ey2, x3+ex3, y3+ey3) ;
	  qual = triangulationMethod(&xNoise, &yNoise, alpha1+ea1, alpha2+ea2, alpha3+ea3, x1, y1, x2, y2, x3, y3, method) ;
	  qual = abs( qual ) ;
	  oNoise  = atan2( (y1-yNoise) , (x1-xNoise) ) - alpha1 ;
	  /*tfloat oNoise2, oNoise3, sinMean, cosMean ;
	  oNoise2 = atan2( (y2-yNoise) , (x2-xNoise) ) - alpha2 ;
	  oNoise3 = atan2( (y3-yNoise) , (x3-xNoise) ) - alpha3 ;
	  sinMean = (sin(oNoise)+sin(oNoise2)+sin(oNoise3))/3;
	  cosMean = (cos(oNoise)+cos(oNoise2)+cos(oNoise3))/3;
	  oNoise  = atan2( sinMean , cosMean ) ;*/
	  
	  errP[ i ] = sqrt( (xTrue-xNoise)*(xTrue-xNoise) + (yTrue-yNoise)*(yTrue-yNoise) ) ;
	  errO[ i ] = oTrue - oNoise ; while( errO[ i ] > PI ) errO[ i ] -= TWOPI ; while( errO[ i ] <= -PI ) errO[ i ] += TWOPI ;
	  Qual[ i ] = qual ;
	}
	
  switch( outputType )
  {
    case 1: s = sqrt ( variance ( errP , n ) ) ; break ;
    case 2: s = sqrt ( variance ( errO , n ) ) * RAD2DEG ; break ;
    case 3: s = mean ( Qual , n ) ; break ;
    default: fprintf( stderr , "triangulationSensitivity(): Bad output type!\n" ) ; return -1 ;
  }
	
	free ( errP ) ;
	free ( errO ) ;
	free ( Qual ) ;
	
  if( thresh > 0.0 )
  {
	  if( s <= thresh ) return 1.0 ;
	  else return 0.0 ;
	}
	else return s ;

}


/**
*  Computes the first order Geometric Dilution of Precision (GDOP) for triangulation,
*  given the robot position (xr,yr), and beacons locations (x1,y1), (x2,y2), and (x3,y3).
*
* @param xr
* @param yr
* @param x1
* @param y1
* @param x2
* @param y2
* @param x3
* @param y3
*
* @return 
*/
tfloat triangulationGDOP(tfloat xr, tfloat yr, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{
	tfloat jacobian[3][3] , det , d1 , d2 , d3 ;
	
	d1 = ( x1 - xr ) * ( x1 - xr ) + ( y1 - yr ) * ( y1 - yr ) ;
	d2 = ( x2 - xr ) * ( x2 - xr ) + ( y2 - yr ) * ( y2 - yr ) ;
	d3 = ( x3 - xr ) * ( x3 - xr ) + ( y3 - yr ) * ( y3 - yr ) ;
	
	jacobian[0][0] = ( y1 - yr ) / d1 ; jacobian[0][1] = ( x1 - xr ) / d1 ; jacobian[0][2] = 1.0 ;
	jacobian[1][0] = ( y2 - yr ) / d2 ; jacobian[1][1] = ( x2 - xr ) / d2 ; jacobian[1][2] = 1.0 ;
	jacobian[2][0] = ( y3 - yr ) / d3 ; jacobian[2][1] = ( x3 - xr ) / d3 ; jacobian[2][2] = 1.0 ;
	
	det = detMatrix33( jacobian ) ;
	
	return 1.0 / fabs( det ) ;
}

/**
* @brief Computes the determinant of a 3x3 matrix.
*
* @param M[][3]
*
* @return 
*/
inline tfloat detMatrix33(tfloat M[][3])
{
  return M[0][0]*M[1][1]*M[2][2] + M[0][1]*M[1][2]*M[2][0] + M[1][0]*M[2][1]*M[0][2] - M[0][2]*M[1][1]*M[2][0] - M[0][1]*M[1][0]*M[2][2] - M[1][2]*M[2][1]*M[0][0] ;
}


#define SWP 20  /* Scale Width Percentage */
/**
*  Scales 'image[]' according to 'mode', 'Max', and 'P1'.
*  Saves scaled image in "map.pgm" and corresponding scale in "scale.pgm"
*
* @param image[]
* @param width
* @param height
* @param mode
* @param Max
* @param P1
*
* @return 
*/
int saveMapAndScale(tfloat image[] , unsigned int width, unsigned int height, unsigned int mode, unsigned int Max, tfloat P1)
{
	tfloat *map = ( tfloat * ) malloc( width * height * sizeof(tfloat) ) ; if( map == NULL ) return -1 ;
	tfloat *scale = ( tfloat * ) malloc( (width/SWP) * height * sizeof(tfloat) ) ; if( scale == NULL ) return -1 ;
	tfloat *map_color = ( tfloat * ) malloc( width * height * 3 * sizeof(tfloat) ) ; if( map_color == NULL ) return -1 ;
	tfloat *scale_color = ( tfloat * ) malloc( (width/SWP) * height * 3 * sizeof(tfloat) ) ; if( scale_color == NULL ) return -1 ;
	
	switch( mode )
	{
	  case 0:
	    map_to_grayscale_lin( image , map , scale , width , height , Max ) ;
	    break;
	  case 1:
	    map_to_grayscale_log( image , map , scale , width , height , Max , P1 ) ;
	    break;
	  case 2:
	    map_to_grayscale_hist( image , map , width , height , Max ) ;
	    break;
	  case 3:
	    map_to_grayscale_sat( image , map , width , height , 100 ) ;
	    map_to_grayscale_lin( map , map , scale , width , height , Max ) ;
	    break;
	  case 4:
	    map_to_grayscale_sat( image , map , width , height , 100 ) ;
	    map_to_grayscale_log( map , map , scale , width , height , Max , P1 ) ;
	    break;
	  default:
	    fprintf(stderr, "saveMapAndScale(): Bad map scaling mode!\n") ;
	    free( map ) ;
	    free( scale ) ;
	    free( map_color ) ;
	    free( scale_color ) ;
	    return -1 ;
	}
	writePGM( map , width , height , Max , "map.pgm" ) ;
	writePGM( scale , width/SWP , height , Max , "scale.pgm" ) ; /* for now, there is no scale for mode 2. To Do */
	
	grayscale2RGB( map , map_color , width , height , Max ) ;
	grayscale2RGB( scale , scale_color , width/SWP , height , Max ) ;
	
	writePPM( map_color , width , height , Max , "map.ppm" ) ;
	writePPM( scale_color , width/SWP , height , Max , "scale.ppm" ) ; /* for now, there is no scale for mode 2. To Do */
	
	/* free memory */
	free( map ) ;
	free( scale ) ;
	free( map_color ) ;
	free( scale_color ) ;
	
	return 0 ;
}

/**
* @brief Convert a grayscale to an RGB image.
*
* @param imageG[]
* @param imageRGB[]
* @param width
* @param height
* @param Max
*/
void grayscale2RGB( tfloat imageG[] , tfloat imageRGB[] , unsigned int width , unsigned int height , unsigned int Max )
{
	unsigned int i , j ;
	tfloat v ;
	color c ;

	for( j = 0 ; j < height ; ++j )
	{
	  for( i = 0 ; i < width ; ++i )
	  {
	    v = imageG [ (height-j-1)*width + i ] ;
	    c = mapRGB( v , 0.0 , Max ) ;
	    imageRGB [ (height-j-1)*width*3 + i*3 + 0 ] = c.r * Max ;
	    imageRGB [ (height-j-1)*width*3 + i*3 + 1 ] = c.g * Max ;
	    imageRGB [ (height-j-1)*width*3 + i*3 + 2 ] = c.b * Max ;
	  }
	}
}

/**
* Return a RGB color value given a scalar v in the range [vmin,vmax]
* In this case each colour component ranges from 0 (no contribution) to
*  1 (fully saturated), modifications for other ranges is trivial.
*  The colour is clipped at the end of the scales if v is outside
*  the range [vmin,vmax]
*  http://stackoverflow.com/questions/7706339/grayscale-to-red-green-blue-matlab-jet-color-scale
*
* @param v
* @param vmin
* @param vmax
*
* @return 
*/
color mapRGB( tfloat v , tfloat vmin , tfloat vmax )
{
   color c = { 1.0 , 1.0 , 1.0 } ; /* white */
   tfloat dv ;

   if (v < vmin) v = vmin ;
   if (v > vmax) v = vmax ;
   dv = vmax - vmin ;

   if ( v < ( vmin + 0.25 * dv ) ) {
      c.r = 0 ;
      c.g = 4 * ( v - vmin ) / dv ;
   } else if ( v < ( vmin + 0.5 * dv ) ) {
      c.r = 0 ;
      c.b = 1 + 4 * ( vmin + 0.25 * dv - v ) / dv ;
   } else if ( v < ( vmin + 0.75 * dv ) ) {
      c.r = 4 * ( v - vmin - 0.5 * dv ) / dv ;
      c.b = 0 ;
   } else {
      c.g = 1 + 4 * ( vmin + 0.75 * dv - v ) / dv ;
      c.b = 0 ;
   }

   return c ;
}


/**
*  Writes a PGM ASCII file in 'fileName'.
*  image[] is the array of values, width/height are the dimensions, Max is the maximum desired value in the file.
*  http://netpbm.sourceforge.net/doc/ppm.html
*  http://en.wikipedia.org/wiki/Netpbm_format
*
* @param image[]
* @param width
* @param height
* @param Max
* @param fileName
*
* @return 
*/
int writePGM( tfloat image[] , unsigned int width , unsigned int height , unsigned int Max , char* fileName )
{
	unsigned int i , j ;
  FILE *file = fopen( fileName , "w" ) ; if( file == NULL ) return -1 ;

	/* write PGM ASCII file */
	fprintf( file , "P2\n" ) ;
	fprintf( file , "%d\n", width ) ;
	fprintf( file , "%d\n", height ) ;
	fprintf( file , "%d\n", Max ) ;
	for( j = 0 ; j < height ; ++j )
	{
	  for( i = 0 ; i < width ; ++i )
	  {
	    fprintf( file , "%u ", ( unsigned int ) image [ (height-j-1)*width + i ] ) ;
	  }
	  fprintf( file , "\n" ) ;
	}
	
	fclose( file ) ;
	
	return 0 ;
}

/**
*  Writes a PPM ASCII file in 'fileName'.
*  image[] is the array of values, width/height are the dimensions, Max is the maximum desired value in the file.
*  http://netpbm.sourceforge.net/doc/ppm.html
*  http://en.wikipedia.org/wiki/Netpbm_format
*
* @param image[]
* @param width
* @param height
* @param Max
* @param fileName
*
* @return 
*/
int writePPM( tfloat image[] , unsigned int width , unsigned int height , unsigned int Max , char* fileName )
{
	unsigned int i , j ;
  FILE *file = fopen( fileName , "w" ) ; if( file == NULL ) return -1 ;

	/* write PGM ASCII file */
	fprintf( file , "P3\n" ) ;
	fprintf( file , "%d\n", width ) ;
	fprintf( file , "%d\n", height ) ;
	fprintf( file , "%d\n", Max ) ;
	for( j = 0 ; j < height ; ++j )
	{
	  for( i = 0 ; i < width ; ++i )
	  {
	    fprintf( file , "%u ", ( unsigned int ) image [ (height-j-1)*width*3 + i*3 ] ) ;
	    fprintf( file , "%u ", ( unsigned int ) image [ (height-j-1)*width*3 + i*3 + 1 ] ) ;
	    fprintf( file , "%u  ", ( unsigned int ) image [ (height-j-1)*width*3 + i*3 + 2 ] ) ;
	  }
	  fprintf( file , "\n" ) ;
	}
	
	fclose( file ) ;
	
	return 0 ;
}


/**
* 
*/
typedef struct {
  unsigned int pos ;
  tfloat value ;
} struct_map_to_grayscale ;

/**
* @brief 
*
* @param a
* @param b
*
* @return 
*/
static int map_to_grayscale_hist_comp ( const void * a , const void * b )
{
  struct_map_to_grayscale * a_ = ( struct_map_to_grayscale * ) a ;
  struct_map_to_grayscale * b_ = ( struct_map_to_grayscale * ) b ;
  if ( a_->value < b_->value ) return -1 ;
  if ( a_->value > b_->value ) return 1 ;
  return 0 ;
}

/**
* @brief 
*
* @param in
* @param out
* @param width
* @param height
* @param numgraylevels
*/
static void map_to_grayscale_hist ( tfloat * in , tfloat * out , unsigned int width , unsigned int height , unsigned int numgraylevels )
{
  struct_map_to_grayscale * tmp = ( struct_map_to_grayscale * ) malloc ( width * height * sizeof ( struct_map_to_grayscale ) ) ;
  unsigned int pos ;
  unsigned int N = (width * height) ;

  if ( tmp == NULL ) return ;
  for ( pos = 0 ; pos < N ; ++ pos ) {
      tmp [ pos ] .pos = pos ;
      tmp [ pos ] .value = in [ pos ] ;
  }

  qsort ( tmp , N , sizeof ( struct_map_to_grayscale ) , map_to_grayscale_hist_comp ) ;
  printf( "min = %f\n" , tmp[ 0 ] .value ) ;
  printf( "max = %f\n" , tmp[ N-1 ] .value ) ;

  for ( pos = 0 ; pos < N ; ++ pos ) {
      out [ tmp [ pos ] .pos ] = pos * numgraylevels / N ;
  }

  free ( tmp ) ;
}

/**
* @brief 
*
* @param in
* @param out
* @param width
* @param height
* @param p
*/
static void map_to_grayscale_sat ( tfloat * in , tfloat * out , unsigned int width , unsigned int height , unsigned int p )
{
  struct_map_to_grayscale * tmp = ( struct_map_to_grayscale * ) malloc ( width * height * sizeof ( struct_map_to_grayscale ) ) ;
  unsigned int pos ;
  unsigned int N = (width * height) ;
  unsigned int Nmax = (width * height) - ( (width * height) / p ) ;
  tfloat max;

  if ( tmp == NULL ) return ;
  for ( pos = 0 ; pos < N ; ++ pos ) {
      tmp [ pos ] .pos = pos ;
      tmp [ pos ] .value = in [ pos ] ;
  }

  qsort ( tmp , N , sizeof ( struct_map_to_grayscale ) , map_to_grayscale_hist_comp ) ;
  max = tmp [ Nmax ] .value ;

  for ( pos = 0 ; pos < N ; ++ pos ) {
      if( in [ pos ] > max ) out [ pos ] = max ;
      else out [ pos ] = in [ pos ] ;
  }

  free ( tmp ) ;
}

/**
* @brief 
*
* @param in
* @param out
* @param scale
* @param width
* @param height
* @param numgraylevels
*/
static void map_to_grayscale_lin ( tfloat * in , tfloat * out , tfloat * scale , unsigned int width , unsigned int height , unsigned int numgraylevels )
{
  unsigned int index , indexMin = 0 , indexMax = 0 , j ;
  unsigned int N = (width * height) ;
  tfloat min = in[0] , max = in[0] ;
  
	/* search extremum value */
	for( index = 0 ; index < N ; ++index )
	{
    if( in[index] < min ) min = in[index] , indexMin = index ;
    if( in[index] > max ) max = in[index] , indexMax = index ;
	}
	printf( "min = %f  @ (%d,%d)\n" , min , indexMin/width , indexMin%width ) ;
	printf( "max = %f  @ (%d,%d)\n" , max , indexMax/width , indexMax%width ) ;
	
	/* rescale values */
	for( index = 0 ; index < N ; ++index )
	{
    out[index] = ( ( in[index] - min ) / ( max - min ) ) * numgraylevels ;
	}
	
	/* create scale */
	for( index = 0 ; index < height ; ++index )
	{
	  for( j = 0 ; j < (width/SWP) ; ++j )
      scale[ index*(width/SWP) + j ] = index * (tfloat)numgraylevels / (tfloat)height ;
	}
}

/**
* @brief 
*
* @param in
* @param out
* @param scale
* @param width
* @param height
* @param numgraylevels
* @param P1
*/
static void map_to_grayscale_log ( tfloat * in , tfloat * out , tfloat * scale , unsigned int width , unsigned int height , unsigned int numgraylevels , tfloat P1 )
{
  unsigned int index , indexMin = 0 , indexMax = 0 , j ;
  unsigned int N = (width * height) ;
  tfloat min = in[0] , max = in[0] ;
  
	/* search extremum value */
	for( index = 0 ; index < N ; ++index )
	{
    if( in[index] < min ) min = in[index] , indexMin = index ;
    if( in[index] > max ) max = in[index] , indexMax = index ;
	}
	printf( "min = %f  @ (%d,%d)\n" , min , indexMin/width , indexMin%width ) ;
	printf( "max = %f  @ (%d,%d)\n" , max , indexMax/width , indexMax%width ) ;
	
	/* rescale values */
	for( index = 0 ; index < N ; ++index )
	{
    out[index] = log( 1 + P1 * (( in[index] - min ) / ( max - min )) ) * (tfloat)numgraylevels / log( 1 + P1 ) ;
	}
	
	/* create scale */
	for( index = 0 ; index < height ; ++index )
	{
	  for( j = 0 ; j < (width/SWP) ; ++j )
      scale[ index*(width/SWP) + j ] = log( 1 + P1 * ( (tfloat)index / (tfloat)height ) ) * (tfloat)numgraylevels / log( 1 + P1 ) ;
	}
}

