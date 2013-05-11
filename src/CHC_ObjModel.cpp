#include "CHC_ObjModel.h"

CHC_ObjModel::CHC_ObjModel(const GLfloat _ZoomDegree = 1.00) {
	ZoomDegree = _ZoomDegree;
	Vertexs.clear();
	TextureCoors.clear();
	Normals.clear();
	Faces.clear();
}

CHC_ObjModel::~CHC_ObjModel() {
	/* Release memories */
	for (unsigned i = 0; i < Vertexs.size(); i++) delete Vertexs[i];
	for (unsigned i = 0; i < TextureCoors.size(); i++) delete TextureCoors[i];
	for (unsigned i = 0; i < Normals.size(); i++) delete Normals[i];
	for (unsigned i = 0; i < Faces.size(); i++)
		for (unsigned j = 0; j < Faces[i].size(); j++)
			delete Faces[i][j];
}

void CHC_ObjModel::ImportMtl() {
	ifstream Fin(MtlFilePath.c_str());
	string opr, str;
	CHC_Material Mtl("NONE");
	while (Fin >> opr) {
		if (opr == "#" || opr == "Tr" || opr == "Tf" || opr == "d") {
			getline(Fin, str);
		}
		if (opr == "Ka") {
			Fin >> Mtl.Ka[0] >> Mtl.Ka[1] >> Mtl.Ka[2];
		}
		if (opr == "Kd") {
			Fin >> Mtl.Kd[0] >> Mtl.Kd[1] >> Mtl.Kd[2];
		}
		if (opr == "Ks") {
			Fin >> Mtl.Ks[0] >> Mtl.Ks[1] >> Mtl.Ks[2];
		}
		if (opr == "illum") {
			Fin >> Mtl.illum;
		}
		if (opr == "Ns") {
			Fin >> Mtl.Ns;
		}
		if (opr == "map_Kd") {
			string map_Kd;
			Fin >> map_Kd;
			if (map_Kd.find(".bmp") != -1) LoadGLTextures(Mtl.texture, map_Kd.c_str());
			if (map_Kd.find(".jpg") != -1) BuildTexture_new(Mtl.texture, map_Kd.c_str());
		}
		if (opr == "newmtl") {
			Fin >> str;
			while (str[0] == ' ') str.erase(0, 1);
			Mtls.push_back(Mtl);
			Mtl = CHC_Material(str);
		}
	}
	Mtls.push_back(Mtl);
}

void CHC_ObjModel::GenViewList() {
	if (ViewList > 0) glDeleteLists(ViewList, 1);
	ViewList = glGenLists(1);
	glNewList(ViewList, GL_COMPILE);
	//glColor3f(1.0, 1.0, 1.0);
	//glDisable(GL_TEXTURE_2D);
	for (unsigned i = 0; i < Faces.size(); i++) {
		for (unsigned j = 0; j < Mtls.size(); j++) {
			if (Mtls[j].Name == FaceMtls[i]) 
				Mtls[j].set();
		}
		//glBindTexture(GL_TEXTURE_2D, 10);
		switch (Faces[i].size())
		{
		case 0:
			break;
		case 1:
			glBegin(GL_POINTS); break;
		case 2:
			glBegin(GL_LINES); break;
		case 3:
			glBegin(GL_TRIANGLES); break;
		case 4:
			glBegin(GL_QUADS); break;
		default:
			glBegin(GL_POLYGON); break;
		}
		for (unsigned j = 0; j < Faces[i].size(); j++) {
			if (Faces[i][j][1] != -1) glTexCoord2f(TextureCoors[Faces[i][j][1]][0], TextureCoors[Faces[i][j][1]][1]);
			glVertex3f(Vertexs[Faces[i][j][0]][0] * ZoomDegree, Vertexs[Faces[i][j][0]][1] * ZoomDegree, Vertexs[Faces[i][j][0]][2] * ZoomDegree);
		}
		glEnd();
	}
	glEndList();
}

void CHC_ObjModel::ImportObj(const string & FilePath) {
	FILE * Fin;
	ObjFilePath = FilePath;
	Fin = fopen(FilePath.c_str(), "r");
	char opr[5000], temp[5000];
	string Mtl;
	int TT = 0;
	while (fscanf(Fin, "%s", opr) != EOF) {
		if ((++TT) % 10000 == 0) 
			printf("%d\n", TT);
		if (!strcmp(opr, "#")) {
			fgets(temp, 4000, Fin);
		}
		if (!strcmp(opr, "mtllib")) {
			fgets(temp, 4000, Fin);
			MtlFilePath = string(temp);
			while (MtlFilePath[0] == ' ') MtlFilePath.erase(0, 1);
			while (MtlFilePath[MtlFilePath.size() - 1] == '\n') MtlFilePath.erase(MtlFilePath.size() - 1, 1);
			ImportMtl();
		}
		if (!strcmp(opr, "usemtl")) {
			fscanf(Fin, "%s", temp);
			Mtl = string(temp);
		}
		if (!strcmp(opr, "v")) {
			GLfloat * t = (GLfloat *) malloc(sizeof(GLfloat) * 3);
			fscanf(Fin, "%f%f%f", &t[0], &t[1], &t[2]);
			Vertexs.push_back(t);
		}
		if (!strcmp(opr, "vt")) {
			GLfloat * t = (GLfloat *) malloc(sizeof(GLfloat) * 2);
			fscanf(Fin, "%f%f", &t[0], &t[1]);
			TextureCoors.push_back(t);
		}
		if (!strcmp(opr, "vn")) {
			GLfloat * t = (GLfloat *) malloc(sizeof(GLfloat) * 3);
			fscanf(Fin, "%f%f%f", &t[0], &t[1], &t[2]);
			Normals.push_back(t);
		}
		if (!strcmp(opr, "f")) {
			char Seg[5000];
			fgets(Seg, 4000, Fin);
			int p = 0;
			while (Seg[p] == ' ') p++;
			unsigned n = strlen(Seg);
			while (Seg[n - 1] == '\n' || Seg[n - 1] == ' ') {
				Seg[n - 1] = '\0';
				n--;
			}
			Seg[n ++] = ' ';
			vector<int *> Poly;
			Poly.clear();
			int j = 0, * t = (int *) malloc(sizeof(int) * 3), s = 0;
			memset(t, 0, sizeof(t));
			for (unsigned int i = p; i < n; i++) {
				if (Seg[i] == ' ' || Seg[i] == '\n') {
					t[j] = s - 1; s = 0;
					Poly.push_back(t);
					t = (int *) malloc(sizeof(int) * 3); j = 0;
					memset(t, 0, sizeof(t));
				}
				if (Seg[i] == '/') {
					t[j] = s - 1; s = 0;
					j ++;
				}
				if (Seg[i] >= '0' && Seg[i] <= '9') {
					s = s * 10 + Seg[i] - '0';
				}
			}
			Faces.push_back(Poly);
			FaceMtls.push_back(Mtl);
		}
	}
	fclose(Fin);
	PrintInfo("log.txt");
	GenViewList();
}

void CHC_ObjModel::ImportObj() {
	ImportObj(ObjFilePath);
}

void CHC_ObjModel::PrintInfo(const string & FilePath) {
	ofstream Fout(FilePath);
	Fout << "Number of vertexs : " << Vertexs.size() << endl;
	for (unsigned i = 0; i < Vertexs.size(); i++) 
		Fout << Vertexs[i][0] << ' ' << Vertexs[i][1] << ' ' << Vertexs[i][2] << endl;
	Fout << "Number of texture coordinates : " << TextureCoors.size() << endl;
	for (unsigned i = 0; i < TextureCoors.size(); i++) 
		Fout << TextureCoors[i][0] << ' ' << TextureCoors[i][1] << endl;
	Fout << "Number of Normals : " << Normals.size() << endl;
	for (unsigned i = 0; i < Normals.size(); i++) 
		Fout << Normals[i][0] << ' ' << Normals[i][1] << ' ' << Normals[i][2] << endl;
	Fout << "Number of Faces : " << Faces.size() << endl;
	for (unsigned i = 0; i < Faces.size(); i++) {
		for (unsigned j = 0; j < Faces[i].size(); j++) Fout << Faces[i][j][0] << '/' << Faces[i][j][1] << '/' << Faces[i][j][2] << ' ';
		Fout << endl;
		Fout << "Material : " << FaceMtls[i] << endl;
	}
	Fout.close();
}

void CHC_ObjModel::Draw() {
	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	glCallList(ViewList);
	/*
	for (unsigned i = 0; i < Faces.size(); i++) {
		for (unsigned j = 0; j < Mtls.size(); j++) {
			if (Mtls[j].Name == FaceMtls[i]) 
				Mtls[j].set();
		}
		switch (Faces[i].size())
		{
		case 0:
			break;
		case 1:
			glBegin(GL_POINTS); break;
		case 2:
			glBegin(GL_LINES); break;
		case 3:
			glBegin(GL_TRIANGLES); break;
		case 4:
			glBegin(GL_QUADS); break;
		default:
			glBegin(GL_POLYGON); break;
		}
		for (unsigned j = 0; j < Faces[i].size(); j++) {
			if (Faces[i][j][1] != -1) glTexCoord2f(TextureCoors[Faces[i][j][1]][0], TextureCoors[Faces[i][j][1]][1]);
			glVertex3f(Vertexs[Faces[i][j][0]][0] * ZoomDegree, Vertexs[Faces[i][j][0]][1] * ZoomDegree, Vertexs[Faces[i][j][0]][2] * ZoomDegree);
		}
		glEnd();
	}
	*/
	//glPopMatrix();
}

void CHC_ObjModel::SetZoomDegree(const GLfloat _ZoomDegree) {
	ZoomDegree = _ZoomDegree;
	GenViewList();
}

int Str2Int(const string & str) {
	int s = 0;
	for (unsigned i = 0; i < str.size(); i++) s = s * 10 + str[i] - '0';
	return s;
}
