#pragma once
#pragma comment(lib,"winmm")

#include <GL/glut.h>
#include <iostream>
#include "Cube.h"
#include<mmsystem.h>

#define SOUND_FILE_NAME_BGM    "    "
#define SOUND_FILE_NAME_CUBE   "./sound/cube.wav "
#define SOUND_FILE_NAME_CLEAR   "./sound/clear.wav"

class Stage
{
	int numStage, numCube;
	int selectCube;
	int saveCube1,saveCube2,saveCube3;
	int map[11][11][11];	// 0�϶� empty, 1�϶� �⺻ ����, 2�϶� Ʋ �ƴ� �� ����, 3�϶� Ʋ �ΰ� ����

	int cubetotalnum;

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

	void CheckCube(int x, int y, int z) { cube[selectCube]->Check(y, x, z); }
};

