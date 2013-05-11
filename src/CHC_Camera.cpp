#include "CHC_Camera.h"

void CHC_Camera::set(float pX, float pY, float pZ, float vX, float vY, float vZ, float uX, float uY, float uZ)
{
	CHC_Vector3 Position	= CHC_Vector3(pX, pY, pZ);   
	CHC_Vector3 View		= CHC_Vector3(vX, vY, vZ);   
	CHC_Vector3 UpVector	= CHC_Vector3(uX, uY, uZ);   
   
	m_P = Position;
	m_pV = View;
	m_U = UpVector;
};

void CHC_Camera::set(CHC_Vector3 pos, CHC_Vector3 view)
{
	m_P = pos;
	m_pV = view;
	m_U = CHC_Vector3(0, 1, 0);
}

//Quaternion Method for 3D Rotation
void CHC_Camera::rotateView(float angle, float x, float y, float z)   
{   
	if (angle == 0.0) return;
	
	float len = sqrt(x * x + y * y + z * z);
	x /= len, y /= len, z /= len;

    CHC_Vector3 vNewView;   
          
    CHC_Vector3 vView = m_pV - m_P;     

    vView.normalize();
      
    float cosTheta = (float)cos(angle);   
    float sinTheta = (float)sin(angle);   
       
    vNewView.v[0]  = (cosTheta + (1 - cosTheta) * x * x)        * vView.v[0];   
    vNewView.v[0] += ((1 - cosTheta) * x * y - z * sinTheta)    * vView.v[1];   
    vNewView.v[0] += ((1 - cosTheta) * x * z + y * sinTheta)    * vView.v[2];   

    vNewView.v[1]  = ((1 - cosTheta) * x * y + z * sinTheta)    * vView.v[0];   
    vNewView.v[1] += (cosTheta + (1 - cosTheta) * y * y)        * vView.v[1];   
    vNewView.v[1] += ((1 - cosTheta) * y * z - x * sinTheta)    * vView.v[2];   
       
    vNewView.v[2]  = ((1 - cosTheta) * x * z - y * sinTheta)    * vView.v[0];   
    vNewView.v[2] += ((1 - cosTheta) * y * z + x * sinTheta)    * vView.v[1];   
    vNewView.v[2] += (cosTheta + (1 - cosTheta) * z * z)        * vView.v[2];   
   
    m_pV = m_P + vNewView;   
}   

void CHC_Camera::moveStraight(float dis)
{
	CHC_Vector3 vView = m_pV - m_P;
	vView.normalize();
	m_P += vView * dis;
	m_pV += vView * dis;
}

void CHC_Camera::strafe(float dis)
{
	CHC_Vector3 vStrafe = m_pV - m_P;
	vStrafe = vStrafe.cross(m_U);

	vStrafe.normalize();

	m_P += vStrafe * dis;
	m_pV += vStrafe * dis;
}

void CHC_Camera::verticalM(float dis)
{
	CHC_Vector3 vView = m_pV - m_P;
	CHC_Vector3 vTemp = vView.cross(m_U);
	vTemp = vTemp.cross(vView);

	vTemp.normalize();

	m_P += vTemp * dis;
	m_pV += vTemp * dis;
}

void CHC_Camera::yaw(float angle)
{
	rotateView(angle, 0, 1, 0);
}

void CHC_Camera::pitch(float angle)
{
	CHC_Vector3 vAxis = m_pV - m_P;
	vAxis = vAxis.cross(m_U);
	vAxis.normalize();
	rotateView(angle, vAxis[0], vAxis[1], vAxis[2]);
}

//Mouse CHC_Camera control
void CHC_Camera::setViewByMouse(int x, int y, float sensX, float sensY)   
{  
    int midX = glutGet(GLUT_WINDOW_WIDTH) >> 1; 
    int midY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;
    float angleY = 0.0f;                              
    float angleZ = 0.0f;                              
    static float currentRotX = 0.0f;
	if (x == midX && y == midY) return;   
      
    glutWarpPointer(midX, midY);
           
    angleY = (float)((midX - x))/sensX;          
    angleZ = (float)((midY - y))/sensY;          
   
    static float lastRotX = 0.0f;      
    lastRotX = currentRotX;    
	
    currentRotX += angleZ;
	
	
	/* Get strafe */
	CHC_Vector3 vAxis = m_pV - m_P;
	vAxis = vAxis.cross(m_U);
	vAxis.normalize();
	if (currentRotX > 1.0f) {
		currentRotX = 1.0f;
		if (lastRotX != 1.0f) {
			rotateView(1.0f - lastRotX, vAxis.v[0], vAxis.v[1], vAxis.v[2]);
		}
	} else 
	if (currentRotX < -1.0f) {
		currentRotX = -1.0f;
		if (lastRotX != -1.0f) {
			rotateView(-1.0f - lastRotX, vAxis.v[0], vAxis.v[1], vAxis.v[2]);
		}
	} else {
		rotateView(angleZ, vAxis.v[0], vAxis.v[1], vAxis.v[2]);
	}
    rotateView(angleY, 0, 1, 0);   
}   

void CHC_Camera::worldUp(float dis)
{
	CHC_Vector3 vTemp(0, dis, 0);
	m_P += vTemp;
	m_pV += vTemp;
}


void CHC_Camera::setLook()
{
	gluLookAt(  m_P[0], m_P[1], m_P[2], 
				m_pV[0], m_pV[1], m_pV[2], 
				m_U[0], m_U[1], m_U[2] );
}

void CHC_Camera::setLook(float discenter)
{
	CHC_Vector3 vTemp = m_pV - m_P;
	vTemp.normalize();
	vTemp *= discenter;
	vTemp += m_P;
	gluLookAt(  m_P[0], m_P[1], m_P[2], 
				vTemp[0], vTemp[1], vTemp[2], 
				m_U[0], m_U[1], m_U[2] );
}