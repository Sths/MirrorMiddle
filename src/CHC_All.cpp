#include "CHC_All.h"

void CHC_all:: load()
{
	int x,y,dir;
	ifstream fin(iFilename);
	fin >> mapn >> mapm >> Mirnum;
	for (int i = 0 ; i < Mirnum; i++){
		fin >> x >> y >> dir;
		CHC_vMi.push_back(CHC_Mirror(x,y,dir));
	}
}
void CHC_all:: print() {
	for (unsigned  i = 0; i < CHC_vMi.size(); i++)
		CHC_vMi[i].Draw();
}