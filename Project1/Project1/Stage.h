#pragma once

#include <GL/glut.h>
#include <iostream>
#include "Cube.h"

class Stage
{
	int numStage, numCube;
	int selectCube;
	int saveCube1, saveCube2, saveCube3;
	int map[11][11][11];

	Cube* cube[10];
	float timeStage;
public:
	Stage();
	Stage(int numStage);
	~Stage();

	void drawStage();
	void updateStage(float elapsedTime);
	void Keyboard(unsigned char key);

	void Stage1();

	int getNumCube() { return numCube; }
	void setSelectCube(int num) { selectCube = num; }
	void setCubeType(int num) { cube[selectCube]->setType(num); }

	void setSaveCube1(int num) { saveCube1 = num; }
	void setSaveCube2(int num) { saveCube2 = num; }
	void setSaveCube3(int num) { saveCube3 = num; }

	void savecube1(int num) { cube[saveCube1]->saveType1(num); }
	void savecube2(int num) { cube[saveCube2]->saveType2(num); }
	void savecube3(int num) { cube[saveCube3]->saveType3(num); }

	void CheckCube(int x, int y, int z) { cube[selectCube]->Check(y, x, z); }


};

