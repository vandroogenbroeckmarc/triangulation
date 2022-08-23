/** 
 * @file toolbox.h
 */

#ifndef __TOOLBOX_H__

#ifdef _WIN32
long int random(void);
void srandom(unsigned int seed);
#endif

#define __TOOLBOX_H__

typedef struct {
  double r , g , b ;
} color ;

void get_angles(tfloat *a1, tfloat *a2, tfloat *a3, tfloat xr, tfloat yr, tfloat or, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3);

tfloat triangulationMethod(tfloat *x, tfloat *y,
						tfloat alpha1, tfloat alpha2, tfloat alpha3,
					  tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3, int method);

tfloat mean( tfloat data[] , unsigned long N );
tfloat variance( tfloat data[] , unsigned long N );

void initRand( void );
tfloat gaussianRand( void );

/*tfloat angleSensitivity(tfloat xTrue, tfloat yTrue,
					              tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3,
					              int method, tfloat sigma, unsigned int n, int outputType, double thresh);

tfloat beaconSensitivity(tfloat xTrue, tfloat yTrue,
					               tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3,
					               int method, tfloat sigma, unsigned int n, int outputType, double thresh);*/


tfloat triangulationSensitivity(tfloat xTrue, tfloat yTrue,
					                      tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3,
					                      int method, tfloat sigmaAngle, tfloat sigmaBeacon, unsigned int n, int outputType, double thresh);
					                      
tfloat triangulationGDOP(tfloat xr, tfloat yr, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3);
tfloat detMatrix33(tfloat M[][3]);

int saveMapAndScale(tfloat image[] , unsigned int Width, unsigned int Height, unsigned int Mode, unsigned int Max, tfloat P1);
int writePGM( tfloat image[] , unsigned int width , unsigned int height , unsigned int Max , char* fileName );
int writePPM( tfloat image[] , unsigned int width , unsigned int height , unsigned int Max , char* fileName );
color mapRGB( double v , double vmin , double vmax );
void grayscale2RGB( tfloat imageG[] , tfloat imageRGB[] , unsigned int width , unsigned int height , unsigned int Max );

#endif

