#ifndef CHC_Camera_H
#define CHC_Camera_H

#include "CHC_Vector3.h"

class CHC_Camera
{
public:
	CHC_Camera() {
		CHC_Camera::set(0, 0, 0, 1, 0, 0, 0, 1, 0);
	}

	//Position, view, upVector
	CHC_Camera(float pX, float pY, float pZ, float vX, float vY, float vZ,
		   float uX, float uY, float uZ) { CHC_Camera::set(pX, pY, pZ, vX, vY, vZ, uX, uY, uZ); }
	//~CHC_Camera();

	void set(float pX, float pY, float pZ, float vX, float vY, float vZ,
		   float uX, float uY, float uZ);
	void set(CHC_Vector3 pos, CHC_Vector3 view);
	
	CHC_Vector3 getPosition() const { return m_P; }
	void setPosition(const CHC_Vector3 &ve) {
		m_P = ve;
	}

	CHC_Vector3 getView() const { return m_pV; }
	void setView(const CHC_Vector3 &ve) { 
		m_pV = ve;
	}

	void moveStraight(float dis);	// 按照视点方向前进
	void strafe(float dis);			// 按照视点方向横向走动
	void verticalM(float dis);		// 按照视点方向直接up走(直接提升)
	void rotateView(float angle, float x, float y, float z);	// 旋转矩阵
	void yaw(float angle);			// 绕y轴
	void pitch(float angle);		// 绕x轴
	void worldUp(float angle);		// 相对于世界系，直接上升
	void setLook();					// 利用OpenGL设置LookAt
	void setViewByMouse(int x, int y, float sensX, float sensY); //鼠标控制
	void setLook(float discenter);					// 利用OpenGL设置LookAt
	
//private:
	CHC_Vector3 m_P, m_pV, m_U;
};

#endif