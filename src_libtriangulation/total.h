/**
 * @file total.h
*/

#ifndef __TOTAL_H__
#define __TOTAL_H__

/**
 * Implementation of the ToTal algorithm 
 * 
 * @param x        Horizontal position of the robot 
 * @param y        Vertical position of the robot
 * @param alpha1   Angle with beacon 1
 * @param alpha2   Angle with beacon 2
 * @param alpha3   Angle with beacon 3
 * @param x1       Horizontal position of beacon 1
 * @param y1       Vertical position of beacon 1
 * @param x2       Horizontal position of beacon 2
 * @param y2       Vertical position of beacon 2
 * @param x3       Horizontal position of beacon 3
 * @param y3       Vertical position of beacon 3
 * @return ??
*/
tfloat triangulationPierlot(tfloat *x, tfloat *y, tfloat alpha1, tfloat alpha2, tfloat alpha3, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3);

tfloat triangulationPierlot2(tfloat *x, tfloat *y, tfloat alpha1, tfloat alpha2, tfloat alpha3, tfloat x1, tfloat y1, tfloat x2, tfloat y2, tfloat x3, tfloat y3);

#endif

