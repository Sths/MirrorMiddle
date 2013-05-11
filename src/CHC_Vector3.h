#ifndef CHC_VECTOR3_H
#define CHC_VECTOR3_H

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include <Windows.h>
#include <stdio.h>
#include <glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <glaux.h>
#include <math.h>

class CHC_Vector3
{
public:
	GLfloat v[3];

	/* Create Function */
	CHC_Vector3() { set(0, 0, 0); }
	CHC_Vector3(GLfloat x, GLfloat y, GLfloat z);
	CHC_Vector3(const GLfloat *ve);
	CHC_Vector3(const CHC_Vector3 &ve);
	
	/* Destructor */
	//~CHC_Vector3();
	
	CHC_Vector3 & operator = (const CHC_Vector3 & ve);
	
	void set(GLfloat x, GLfloat y, GLfloat z);
	void normalize();
	
	GLfloat operator[](int i) const;
	GLfloat length() const;
	GLfloat lengthSqr() const;

	CHC_Vector3& operator+=(const CHC_Vector3& ve);
	CHC_Vector3& operator-=(const CHC_Vector3& ve);
	CHC_Vector3& operator*=(GLfloat k);
	CHC_Vector3& operator/=(GLfloat k);
	CHC_Vector3 operator+(const CHC_Vector3& ve) const;
	CHC_Vector3 operator-(const CHC_Vector3& ve) const;
	CHC_Vector3 operator*(GLfloat k) const;
	CHC_Vector3 operator/(GLfloat k) const;
	CHC_Vector3 operator-() const;
	CHC_Vector3 cross(const CHC_Vector3& ve) const;
	float dot(const CHC_Vector3& ve) const;

	static const CHC_Vector3 ZERO;
	static const CHC_Vector3 X_AXIS;
	static const CHC_Vector3 Y_AXIS;
	static const CHC_Vector3 Z_AXIS;
};

#endif