#ifndef CHC_IMPORTER_H
#define CHC_IMPORTER_H

#include <assimp/Importer.hpp>      // C++ importer interface #include <assimp/scene.h>           
#include <assimp/scene.h>			// Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/matrix4x4.h>
#include <assimp/ai_assert.h>
#include <assimp/cimport.h>
#include <assimp/color4.h>

#include <glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <GLAUX.H>
#include <string>
using namespace std;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class CHC_Importer {
	Assimp::Importer importer;
	const aiScene * scene;
	CHC_Importer() {}
	~CHC_Importer() { aiReleaseImport(scene); }
	bool Import(const string & pFile);
	void get_bounding_box (aiVector3D * min, aiVector3D* max);
	void get_bounding_box_for_node (const struct aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo);
};

#endif