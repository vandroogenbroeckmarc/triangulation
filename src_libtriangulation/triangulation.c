/**
* @file triangulation.c
* @author Vincent Pierlot  [ vpierlot@gmail.com ]
* @date April 2013
* @version: 0.7
* 
* Three Object Triangulation algorithms implementation, simulation and benchmarking
* compile with: make
* run with: ./triangulation [options]
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "const.h"
#include "toolbox.h"


#define AUTHOR                  "Vincent Pierlot"
#define EMAIL                   "vpierlot@gmail.com"
#define VERSION                 "0.7"
#define DEFAULT_PROGNAME        "triangulation"


int test0 (tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3);
int test1 (tfloat alpha1, tfloat alpha2, tfloat alpha3, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int m);
int test2 (tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int m);
int test3 (tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int m,
           tfloat xstart, tfloat xend, tfloat ystart, tfloat yend, unsigned int n);
int test4 (tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3,
           int m, tfloat sigmaAngle, tfloat sigmaBeacon, unsigned int n, int O);
int test5 (tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int m, tfloat sigmaAngle, tfloat sigmaBeacon, unsigned int n,
           tfloat xstart, tfloat xend , tfloat ystart , tfloat yend, tfloat step, unsigned int map, int O, double thresh);

void usage(const char *progName);


/**
* @brief Print usage informations. 
*
* Print usage informations,
* the only argument is <progName> and is typically argv[0]
*
* @param progName
*/
void usage( const char *progName )
{
  fprintf(stderr ,
          DEFAULT_PROGNAME " " VERSION " by " AUTHOR " [" EMAIL "]\n"
          "Three Object Triangulation algorithms implementation, simulation and benchmarking.\n"
          "http://www2.ulg.ac.be/telecom/triangulation/\n"
          "http://hdl.handle.net/2268/89435\n"
          "Usage: %s [options]\n"
          "[options]:\n"
          "  -t  int    Test to execute (default=5):\n"
          "             0: gets angles from robot pose (x;y;o). Displays angles (a;b;c).\n"
          "             1: triangulates from measured angles (a;b;c). Displays robot pose (x;y;o).\n"
          "             2: gets angles from robot pose (x;y;o) and triangulates with measured angles. Displays angles and pose.\n"
          "             3: runs triangulation method n times from random positions in the grid [-x,X]*[y,Y]. Displays execution time.\n"
          "             4: runs triangulation sensitivity analysis from robot position (x;y). (see -O for output).\n"
          "             5: runs triangulation sensitivity analysis for each point in the grid [-x,X]*[y,Y]. (see -O for output).\n"
          "                Writes PGM images \"map.pgm\" and \"scale.pgm\" in current directory. Displays step, min and max values.\n"
          "  -m  int    Triangulation method to use (default=1). For all tests.\n"
          "              1: Pierlot (ToTal)  2: Esteves          3: FontLlagunes (T)  4: Zalama\n"
          "              5: McGillem (T)     6: McGillem (G)     7: Easton            8: Hmam\n"
          "              9: Cohen (T)       10: Cohen (G)       11: Cohen (G)*       12: Tsukiyama\n"
          "             13: Tsukiyama*      14: Madsen          15: Lukic            16: Lukic*\n"
          "             17: Tienstra        18: Ligas           19: FontLlagunes (G) 20: Kaestner\n"
          "             21: Collins         22: Cassini\n"
          "             (*) original method from the paper (typically slower than my implementation)\n"
          "             (G) Geometric solution\n"
          "             (T) Trigonometric solution\n"
          "  -x  float  X robot position. For tests 0, 2, 4. (default=0.0)\n"
          "             X min value of test grid. For tests 3, 5. (default=-2.0)\n"
          "  -y  float  Y robot position. For tests 0, 2, 4. (default=0.0)\n"
          "             Y min value of test grid. For tests 3, 5. (default=-2.0)\n"
          "  -o  float  Robot orientation relative to X axis [deg]. For tests 0, 2, 4. (default=0.0)\n"
          "  -a  float  alpha1 angle [deg]. For test 1. (default=+90)\n"
          "  -b  float  alpha2 angle [deg]. For test 1. (default=-150)\n"
          "  -c  float  alpha3 angle [deg]. For test 1. (default=-30)\n"
          "  -1  float  X1 beacon1 position. For all tests. (default=0.0)\n"
          "  -2  float  Y1 beacon1 position. For all tests. (default=+1.0)\n"
          "  -3  float  X2 beacon2 position. For all tests. (default=-0.866)\n"
          "  -4  float  Y2 beacon2 position. For all tests. (default=-0.5)\n"
          "  -5  float  X3 beacon3 position. For all tests. (default=+0.866)\n"
          "  -6  float  Y3 beacon3 position. For all tests. (default=-0.5)\n"
          "  -O  int    Output of the sensitivity analysis. For tests 4, 5. (default=1)\n"
          "             1: std deviation of position error, 2: std deviation of orientation error, 3: return value of method.\n"
          "  -X  float  X max value of test grid. For tests 3, 5. (default=+2.0)\n"
          "  -Y  float  Y max value of test grid. For tests 3, 5. (default=+2.0)\n"
          "  -p  float  Discretization step of the test grid. For test 5. (default=0.02)\n"
          "  -A  float  Standard deviation of the gaussian noise applied to angles in [deg]. For tests 4, 5. (default=0.1)\n"
          "  -B  float  Standard deviation of the gaussian noise applied to beacons coordinates. For tests 4, 5. (default=0.0)\n"
          "  -n  int    Number of tests for the execution time and the sensitivity analysis. For tests 3, 4, 5. (default=100)\n"
          "  -M  int    Map used to display results from the sensitivity analysis. For test 5. (default=2)\n"
          "             0: Linear.\n"
          "             1: Logarithmic.\n"
          "             2: Histogram equalized.\n"
          "             3: Linear after removing outliers (1 percent of the highest values).\n"
          "             4: Logarithmic after removing outliers (1 percent of the highest values).\n"
          "  -T  float  Threshold for the sensitivity analysis output (must be >= 0 to be active). For test 5. (default=-1)\n"
          "  -h         Displays this help and exit.\n"
          "\n"
          , progName ) ;
  exit( -1 ) ;
}


int main ( int argc , char *argv[] )
{
  /* default testing mode */
  int t = 5 ;
  
  /* default triangulation method */
  int m = 1 ;
  
  /* default robot position and orientation */
	tfloat xr = 0 ;
	tfloat yr = 0 ;
	tfloat or = 0 ;
	
  /* default angles (from default robot position and orientation, and beacon locations) */
	tfloat a1 =   90.0 * DEG2RAD ;
	tfloat a2 = -150.0 * DEG2RAD ;
	tfloat a3 =  -30.0 * DEG2RAD ;
	
	/* default beacon locations (regular triangle) */
	tfloat x1 =  0.0   ;
	tfloat y1 = +1.0   ;
	tfloat x2 = -sqrt(3.0)/2 ;
	tfloat y2 = -0.5   ;
	tfloat x3 = +sqrt(3.0)/2 ;
	tfloat y3 = -0.5   ;
	
	/* default std dev for sensitivity analysis (in [deg] for angles) */
	tfloat sigmaAngle  = 0.1 * DEG2RAD ;
	tfloat sigmaBeacon = 0.0 ;
	
  /* default bounds, number of points in image edge, number of tests for sensitivity analysis */
  tfloat xstart  = -2.0 ;
  tfloat xend    = +2.0 ;
  tfloat ystart  = -2.0 ;
  tfloat yend    = +2.0 ;
  tfloat step    = 0.02 ;
  tfloat thresh  = -1.0 ;
  unsigned int n = 100 ;
  
  /* default map mode for the sensitivity analysis */
  unsigned int map = 2 ;
  
  /* default output for the sensitivity analysis */
  int O = 1 ;
  
  int optionChar;
  char optString[] = "t:m:x:y:o:A:B:a:b:c:p:n:O:1:2:3:4:5:6:X:Y:M:T:h" ;

  /* Parse Command line */
  while( ( optionChar = getopt(argc, argv, optString) ) != -1 )
  {
    switch( optionChar )
    {
        case '?' : return -1 ; break ; /* erroneous option or missing argument */
        case 't' : t = atoi( optarg ) ; break ;
        case 'm' : m = atoi( optarg ) ; break ;
        case 'x' : xr = atof( optarg ) ; xstart = xr ; break ;
        case 'y' : yr = atof( optarg ) ; ystart = yr ; break ;
        case 'o' : or = atof( optarg )*DEG2RAD ; break ;
        case 'A' : sigmaAngle = atof( optarg )*DEG2RAD ; break ;
        case 'B' : sigmaBeacon = atof( optarg ) ; break ;
        case 'a' : a1 = atof( optarg )*DEG2RAD ; break ;
        case 'b' : a2 = atof( optarg )*DEG2RAD ; break ;
        case 'c' : a3 = atof( optarg )*DEG2RAD ; break ;
        case 'p' : step = atof( optarg ) ; break ;
        case 'n' : n = atoi( optarg ) ; break ;
        case 'O' : O = atoi( optarg ) ; break ;
        case '1' : x1 = atof( optarg ) ; break ;
        case '2' : y1 = atof( optarg ) ; break ;
        case '3' : x2 = atof( optarg ) ; break ;
        case '4' : y2 = atof( optarg ) ; break ;
        case '5' : x3 = atof( optarg ) ; break ;
        case '6' : y3 = atof( optarg ) ; break ;
        case 'X' : xend = atof( optarg ) ; break ;
        case 'Y' : yend = atof( optarg ) ; break ;
        case 'M' : map = atoi( optarg ) ; break ;
        case 'T' : thresh = atof( optarg ) ; break ;
        case 'h' : usage( argv[0] ) ; return 0 ;
        default : ;
    }
  }
  
  switch( t )
  {
    case 0: return test0( xr , yr , or , x1 , y1 , x2 , y2 , x3 , y3 ) ;
    case 1: return test1( a1 , a2 , a3 , x1 , y1 , x2 , y2 , x3 , y3 , m ) ;
    case 2: return test2( xr , yr , or , x1 , y1 , x2 , y2 , x3 , y3 , m ) ;
    case 3: return test3( x1 , y1 , x2 , y2 , x3 , y3 , m , xstart , xend , ystart , yend , n ) ;
    case 4: return test4( xr , yr , or , x1 , y1 , x2 , y2 , x3 , y3 , m , sigmaAngle , sigmaBeacon , n , O ) ;
    case 5: return test5( x1 , y1 , x2 , y2 , x3 , y3 , m , sigmaAngle , sigmaBeacon , n , xstart , xend , ystart , yend , step , map , O , thresh ) ;
    default: fprintf( stderr , "main(): Bad test number!\n" ) ; return -1 ;
  }
  
}


/*
 *
*/
int test0 (tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3)
{	
	tfloat alpha1 = 0.0 ;
	tfloat alpha2 = 0.0 ;
	tfloat alpha3 = 0.0 ;
	
	get_angles( &alpha1 , &alpha2 , &alpha3 , xr , yr , or , x1 , y1 , x2 , y2 , x3 , y3 ) ;
	
	printf( "\nMeasured angles:\n" ) ;
	printf( "a = %f [deg]\n"   , alpha1*RAD2DEG ) ;
	printf( "b = %f [deg]\n"   , alpha2*RAD2DEG ) ;
	printf( "c = %f [deg]\n\n" , alpha3*RAD2DEG ) ;

	return 0 ;
}


/*
 *
*/
int test1 (tfloat alpha1, tfloat alpha2, tfloat alpha3, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int m)
{	
	tfloat x = 0.0 ;
	tfloat y = 0.0 ;
	tfloat o = 0.0 ;
	
	tfloat Q = 0.0 ;
	
	Q = triangulationMethod( &x , &y , alpha1 , alpha2 , alpha3 , x1 , y1 , x2 , y2 , x3 , y3 , m ) ;
	o = atan2( (y1-y) , (x1-x) ) - alpha1 ;
	
	printf( "\nComputed position:\n" ) ;
	printf( "x = %f\n", x ) ;
	printf( "y = %f\n", y ) ;
	printf( "o = %f [deg]\n\n" , o*RAD2DEG ) ;
	printf( "Error measure = %f\n\n" , Q) ;

	return 0 ;
}


/*
 *
*/
int test2 (tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int m)
{	
	tfloat x = 0 ;
	tfloat y = 0 ;
	tfloat o = 0 ;
	
	tfloat alpha1 = 0 ;
	tfloat alpha2 = 0 ;
	tfloat alpha3 = 0 ;
	
	tfloat Q = 0 ;
	
	get_angles( &alpha1 , &alpha2 , &alpha3 , xr , yr , or , x1 , y1 , x2 , y2 , x3 , y3 ) ;
	
	Q = triangulationMethod( &x , &y , alpha1 , alpha2 , alpha3 , x1 , y1 , x2 , y2 , x3 , y3 , m ) ;
	o = atan2( (y1-y) , (x1-x) ) - alpha1 ;
	
	printf( "\nMeasured angles:\n" ) ;
	printf( "a = %f [deg]\n" , alpha1*RAD2DEG ) ;
	printf( "b = %f [deg]\n" , alpha2*RAD2DEG ) ;
	printf( "c = %f [deg]\n" , alpha3*RAD2DEG ) ;
	printf( "\nComputed position:\n") ;
	printf( "x = %f\n" , x ) ;
	printf( "y = %f\n" , y ) ;
	printf( "o = %f [deg]\n\n" , o*RAD2DEG ) ;
	printf( "Error measure = %f\n\n" , Q ) ;

	return 0 ;
}


/*
 *
*/
int test3 ( tfloat x1 , tfloat y1 , tfloat x2 , tfloat y2 , tfloat x3 , tfloat y3 , int m ,
            tfloat xstart, tfloat xend , tfloat ystart , tfloat yend , unsigned int n )
{
	tfloat xi = 0.0 ;
	tfloat yi = 0.0 ;
	
	tfloat *alpha1M = ( tfloat * ) malloc( n * sizeof(tfloat) ) ; if( alpha1M == NULL ) return -1 ;
	tfloat *alpha2M = ( tfloat * ) malloc( n * sizeof(tfloat) ) ; if( alpha2M == NULL ) return -1 ;
	tfloat *alpha3M = ( tfloat * ) malloc( n * sizeof(tfloat) ) ; if( alpha3M == NULL ) return -1 ;
	
	int i , j ;
	double t , tmin = 0.0 ;
	
	initRand() ;
	srandom( 0 ) ;
	
	for( i = 0 ; i < n ; ++i )
  {
    xi = ( ( (tfloat) random() / (tfloat) RAND_MAX ) * ( xend - xstart ) ) + xstart ;
    yi = ( ( (tfloat) random() / (tfloat) RAND_MAX ) * ( yend - ystart ) ) + ystart ;
    get_angles( &alpha1M[i] , &alpha2M[i] , &alpha3M[i] , xi , yi , 0.0 , x1 , y1 , x2 , y2 , x3 , y3 ) ;
  }
  
	for( j = 0 ; j < 10 ; ++j )
  {
  
#ifdef _WIN32 /* also valid for Linux but not precise */
    clock_t startClock = clock() ;
#else
	  struct timespec startTime , endTime ;
	  clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &startTime ) ;
#endif
	
    for( i = 0 ; i < n ; ++i )
    {
      triangulationMethod( &xi , &yi , alpha1M[i] , alpha2M[i] , alpha3M[i] , x1 , y1 , x2 , y2 , x3 , y3 , m ) ;
    }

#ifdef _WIN32 /* also valid for Linux but not precise */
	  clock_t endClock = clock() ;	
	  t = ( (double) (endClock - startClock) ) / CLOCKS_PER_SEC ;
#else
	  clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &endTime ) ;
	  t = ( (double) ((endTime.tv_sec-startTime.tv_sec)+(endTime.tv_nsec-startTime.tv_nsec)/1000000000.0)) ;
	  /*printf( "Duration = %10.5f [s]\n" , t ) ;*/
#endif
	  
	  if ( j == 0 ) tmin = t ;
	  if ( t < tmin ) tmin = t ;
	}
	
	printf( "Duration = %10.5f [s]\n" , tmin ) ;
	
	free( alpha1M ) ;
	free( alpha2M ) ;
	free( alpha3M ) ;

	return 0 ;
}


/*
 *
*/
int test4 (tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3,
           int m, tfloat sigmaAngle, tfloat sigmaBeacon, unsigned int n, int O)
{
	tfloat alpha1 = 0.0 ;
	tfloat alpha2 = 0.0 ;
	tfloat alpha3 = 0.0 ;
	
	tfloat s = 0.0 ;
	
	get_angles( &alpha1 , &alpha2 , &alpha3 , xr , yr , or , x1 , y1 , x2 , y2 , x3 , y3 ) ;
	
	s = triangulationSensitivity( xr , yr , x1 , y1 , x2 , y2 , x3 , y3 , m , sigmaAngle , sigmaBeacon , n , O , -1 ) ;
	
	printf( "\nMeasured angles:\n" ) ;
	printf( "a = %f [deg]\n" , alpha1*RAD2DEG ) ;
	printf( "b = %f [deg]\n" , alpha2*RAD2DEG ) ;
	printf( "c = %f [deg]\n" , alpha3*RAD2DEG ) ;
	
  switch( O )
  {
    case 1: printf( "\nPosition error standard deviation: %f\n" , s ) ; break ;
    case 2: printf( "\nOrientation error standard deviation: %f [deg]\n" , s ) ; break ; /* already converted in degree */
    case 3: printf( "\nMean error measure: %f\n" , s ) ; break ;
    default: fprintf( stderr , "test4(): Bad output type!\n" ) ; return -1 ;
  }

	return 0 ;
}


/*
 *
*/
int test5 ( tfloat x1 , tfloat y1 , tfloat x2 , tfloat y2 , tfloat x3 , tfloat y3 , int m , tfloat sigmaAngle , tfloat sigmaBeacon , unsigned int n ,
            tfloat xstart , tfloat xend , tfloat ystart , tfloat yend , tfloat step , unsigned int map , int O , double thresh )
{
	tfloat xi = 0.0 , yi = 0.0 ;
	
	unsigned int p = round( ( xend - xstart ) / step ) + 1 ;
	unsigned int q = round( ( yend - ystart ) / step ) + 1 ;
	
	tfloat *errorPM = ( tfloat * ) malloc( p * q * sizeof(tfloat) ) ; if( errorPM == NULL ) return -1 ;
	
	int i , j ;
	
	printf( "Angles standard deviation  = %f [deg]\n" , sigmaAngle*RAD2DEG ) ;
	printf( "Beacons standard deviation  = %f\n" , sigmaBeacon ) ;
	printf( "grid X limits = %f to %f\n" , xstart , xend ) ;
	printf( "grid Y limits = %f to %f\n" , ystart , yend ) ;
	printf( "grid step = %f\n" , step ) ;
	
	for( yi = ystart, j = 0 ; j < q ; j++ )
	{
	  for( xi = xstart, i = 0 ; i < p ; i++ )
	  {
	    switch ( m )
	    {
	      default :
	        errorPM[j*p + i] = triangulationSensitivity( xi , yi , x1 , y1 , x2 , y2 , x3 , y3 , m , sigmaAngle , sigmaBeacon , n , O , thresh ) ;
	        break ;
	      case 101 :
	        errorPM[j*p + i] = triangulationGDOP( xi , yi , x1 , y1 , x2 , y2 , x3 , y3 ) ;
	        break;
      }
	    xi += step ;
	  }
	  yi += step ;
	}
	
	saveMapAndScale( errorPM , p , q , map , 255 , 10 ) ;
	
	free( errorPM ) ;

	return 0 ;
}

