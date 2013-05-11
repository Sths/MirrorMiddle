#ifndef CHC_OBJMODEL_H
#define CHC_OBJMODEL_H

#include "CHC_Constants.h"
#include "CHC_Material.h"
#include <glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class CHC_ObjModel {
private:
	vector<GLfloat *> Vertexs;						// coordinates of the vertexs
	vector<GLfloat *> TextureCoors;					// coordinates of the textures
	vector<GLfloat *> Normals;						// coordinates of the normals
	vector<vector<int *>> Faces;					// index of vertex/texture/normal in faces
	vector<string> FaceMtls;						// which material that faces use
	vector<CHC_Material> Mtls;						// materials

	string ObjInfo;								// # line of the obj file
	string ObjFilePath;							// path of OBJ file
	string MtlFilePath;							// path of MTL file

	GLuint ViewList;								// view lists
	void GenViewList();								// generate new view lists, only call after import obj file;

	GLfloat ZoomDegree;								// degree of zoom

	void ImportMtl();

public:
	CHC_ObjModel() {}
	CHC_ObjModel(const GLfloat _ZoomDegree);
	~CHC_ObjModel();
	void ImportObj(const string & FilePath);
	void ImportObj();
	void PrintInfo(const string & FilePath);
	void Draw();
	void SetZoomDegree(const GLfloat _ZoomDegree);
};

int Str2Int(const string & str);
#endif