#include "CHC_Line.h"

CHC_Line::CHC_Line() {
	S.set(0, 0, 0);		
	T.set(0, 0, 0);
}

CHC_Line::CHC_Line(const CHC_Vector3 & _S, const CHC_Vector3 & _T) {
	S = _S;
	T = _T;
}

CHC_Vector3 CHC_Line::operator[](unsigned int id) {
	if (id == 0) return S;
	if (id == 1) return T;
	else return CHC_Vector3(0, 0, 0);
}

float CHC_Line::istYequal0(CHC_Vector3 & P) {
	if (S[1] == T[1]) return 0;

	CHC_Vector3 Temp = T - S ;
	Temp.normalize();
	float  r = -1 * S[1] / Temp[1];
	P = Temp * r + S;
	return r;
}

float CHC_Line::isItersectionplane(CHC_Vector3 p1 , CHC_Vector3 n, CHC_Vector3 & P)
{
	if ((S - T).dot(n) == 0 ) return 0;

	CHC_Vector3 Temp = T - S;
	Temp.normalize();
	float r;
	r = n[0] * (p1[0]- S[0]) + n[1] * (p1[1] - S[1]) + n[2] * (p1[2] - S[2]);
	r = r / (n[0] * Temp[0] + n[1] * Temp[1] + n[2]  * Temp[2]);
	P = S + Temp * r;
	return r;
}

BOOL CHC_Line::isOnMirror(CHC_Vector3 p1,CHC_Vector3 x1,CHC_Vector3 x2, CHC_Vector3 x3,CHC_Vector3 x4)
{
	if(((x1 - p1).cross(x2 - p1)).dot((x3 - p1).cross(x4 - p1)) < 0 ) return FALSE;
	if(((x4 - p1).cross(x1 - p1)).dot((x2 - p1).cross(x3 - p1)) < 0 ) return FALSE;
	return TRUE;
}

