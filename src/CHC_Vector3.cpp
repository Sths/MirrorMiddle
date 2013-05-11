#include "CHC_Vector3.h"

const CHC_Vector3 CHC_Vector3::ZERO(0.0, 0.0, 0.0);
const CHC_Vector3 CHC_Vector3::X_AXIS(1.0, 0.0, 0.0);
const CHC_Vector3 CHC_Vector3::Y_AXIS(0.0, 1.0, 0.0);
const CHC_Vector3 CHC_Vector3::Z_AXIS(0.0, 0.0, 1.0);

CHC_Vector3::CHC_Vector3(GLfloat x, GLfloat y, GLfloat z) {
	set(x, y, z);
}

CHC_Vector3::CHC_Vector3(const GLfloat *ve) {
	set(ve[0], ve[1], ve[2]);
}

CHC_Vector3::CHC_Vector3(const CHC_Vector3 &ve) {
	set(ve.v[0], ve.v[1], ve.v[2]);
}

CHC_Vector3 & CHC_Vector3::operator= (const CHC_Vector3& ve) {
	set(ve.v[0], ve.v[1], ve.v[2]);
	return *this;
}

void CHC_Vector3::set(GLfloat x, GLfloat y, GLfloat z) {
	v[0] = x, v[1] = y, v[2] = z;
}

CHC_Vector3& CHC_Vector3::operator+=(const CHC_Vector3& ve)
{
	v[0] += ve.v[0];
	v[1] += ve.v[1];
	v[2] += ve.v[2];
	return *this;
}

CHC_Vector3& CHC_Vector3::operator-=(const CHC_Vector3& ve)
{
	v[0] -= ve.v[0];
	v[1] -= ve.v[1];
	v[2] -= ve.v[2];
	return *this;
}

CHC_Vector3& CHC_Vector3::operator*=(GLfloat k)
{
	v[0] *= k, v[1] *= k, v[2] *= k;
	return *this;
}

CHC_Vector3& CHC_Vector3::operator/=(GLfloat k)
{
	v[0] /= k, v[1] /= k, v[2] /= k;
	return *this;
}

CHC_Vector3 CHC_Vector3::operator+(const CHC_Vector3& ve) const
{
	return CHC_Vector3(v[0]+ve.v[0], v[1]+ve.v[1], v[2]+ve.v[2]);
}

CHC_Vector3 CHC_Vector3::operator-(const CHC_Vector3& ve) const
{
	return CHC_Vector3(v[0]-ve.v[0], v[1]-ve.v[1], v[2]-ve.v[2]);
}

CHC_Vector3 CHC_Vector3::operator*(GLfloat k) const
{
	return CHC_Vector3(v[0]*k, v[1]*k, v[2]*k);
}
CHC_Vector3 CHC_Vector3::operator/(GLfloat k) const
{
	return CHC_Vector3(v[0]/k, v[1]/k, v[2]/k);
}
CHC_Vector3 CHC_Vector3::operator-() const
{
	return CHC_Vector3(-v[0], -v[1], -v[2]);
}

GLfloat CHC_Vector3::length() const
{
	return sqrt(lengthSqr());
}

GLfloat CHC_Vector3::lengthSqr() const 
{
	return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

void CHC_Vector3::normalize()
{
	float len = length();
	if (len > 0) {
		v[0] /= len;
		v[1] /= len;
		v[2] /= len;
	}
}

GLfloat CHC_Vector3::operator[](int i) const
{
	//Assume i in [0, 2]
	if (i < 0) return v[0];
	if (i > 2) return v[2];
	return v[i];
}

CHC_Vector3 CHC_Vector3::cross(const CHC_Vector3& ve) const
{
	return CHC_Vector3(v[1] * ve.v[2] - v[2] * ve.v[1], 
				   v[2] * ve.v[0] - v[0] * ve.v[2],
				   v[0] * ve.v[1] - v[1] * ve.v[0]);
}

float CHC_Vector3::dot(const CHC_Vector3& ve) const
{
	return v[0] * ve[0] + v[1] * ve[1] + v[2] * ve[2];
}