#ifndef CHC_LINE_H
#define CHC_LINE_H

#include "CHC_Vector3.h"

class CHC_Line
{
public:
	CHC_Line();
	CHC_Line(const CHC_Vector3 & _S, const CHC_Vector3 & _T);

	CHC_Vector3 operator[](unsigned int i);			// [0]: S,  [1]: T
	float istYequal0(CHC_Vector3 & P);				// intersection with Y = 0 Plane
	float isItersectionplane(CHC_Vector3 p1, CHC_Vector3 n, CHC_Vector3 & P) ; // intersection with plane defined by n & p1.
	BOOL isOnMirror(CHC_Vector3 p1, CHC_Vector3 x1, CHC_Vector3 x2,CHC_Vector3 x3, CHC_Vector3 x4); // check if the intersection point p1 is on the mirror defined by x1 & x2 & x3 & x4.

private:
	CHC_Vector3 S, T;
};

#endif