#include "Stage.h"

Stage::Stage()
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;
}

Stage::Stage(int numStage) : numStage(numStage)
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;
	selectCube = 0;

	if (numStage == 1) {
		numCube = 3;
		Stage1();
	}
}

Stage::~Stage()
{
	for (int i = 0; i < numCube; ++i)
		delete cube[i];

	delete[] cube;
}

void Stage::drawStage()
{
	// map 그리기

	//
	if (selectCube < numCube)
		cube[selectCube]->drawCube();
}

void Stage::updateStage()
{
	// 충돌체크 추가

}

void Stage::Keyboard(unsigned char key)
{
	if (selectCube < numCube)
		if (cube[selectCube]->getType() == 0)
			cube[selectCube]->Keyboard(key);
}

void Stage::Stage1()
{
	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(1, i);
}