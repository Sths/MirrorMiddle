#ifndef CHC_MIRROR_H
#define CHC_MIRROR_H

#include "CHC_Object.h"
#include "CHC_Vector3.h"
#include "CHC_ObjModel.h"
#include "CHC_Constants.h"
#include <vector>
using namespace std;

class CHC_Mirror:CHC_Object {
private:
	int type;
public:
	//static vector<CHC_ObjModel> Models;
	static CHC_ObjModel Models;
	CHC_Mirror();
	CHC_Mirror(int x, int y, int dir, int type);
	CHC_Mirror(CHC_Vector3 _Position, int dir, int type);
	void Set_Position(int x, int y);
	void Set_Direction(int dir);
	void Set_Type(int _type);
	void Load();
	void Draw();
};


#endif