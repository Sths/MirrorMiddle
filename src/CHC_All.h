#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include "CHC_Vector3.h"
#include "CHC_Camera.h"
#include "CHC_Mirror.h" 
#include "CHC_Constants.h"

#include<iostream>
#include<fstream>
#include<vector>

class CHC_all{
protected:
	vector<CHC_Mirror> CHC_vMi;
	int Mirnum;
	int mapn,mapm;
	vector<vector<int>> record;

	//vector<CHC_>
public:
	CHC_all(){}
	void load();
	void refresh();
	void print();
};