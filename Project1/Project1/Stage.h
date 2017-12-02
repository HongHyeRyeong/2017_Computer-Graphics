#pragma once

#include <GL/glut.h>
#include <iostream>
#include "Cube.h"

class Stage
{
	int numStage, numCube;
	int selectCube;
	int map[11][11][11];
	Cube* cube[10];
	float timeStage;
public:
	Stage();
	Stage(int numStage);
	~Stage();

	void drawStage();
	void updateStage();
	void Keyboard(unsigned char key);

	void Stage1();

	int getNumCube() { return numCube; }
	void setSelectCube(int num) { selectCube = num; }
	void setCubeType(int num) { cube[selectCube]->setType(num); }
};

