#include "Stage.h"

Stage::Stage()
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				map[y][x][z] = 0;
}

Stage::Stage(int numStage) : numStage(numStage)
{
	for (int i = 0; i < 10; ++i)
		cube[i] = NULL;
	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				map[y][x][z] = 0;
	
	selectCube = 0;
	
	saveCube1 = 0;
	saveCube2 = 1;
	saveCube3 = 2;

	if (numStage == 1) {
		numCube = 3;
		timeStage = 60 * 5;	// 5분
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
	// 큐브 그리기 고정
	if (selectCube < numCube&&cube[selectCube]->getType() == 0)
		cube[selectCube]->drawCube();

	// map 그리기
	glPushMatrix();
	glTranslatef(-50, 5, 50);

	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {
				if (map[y][x][z] == 1) {
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(0.0, 0.5, 1.0, 0.5);
					glutSolidCube(10);
					glDisable(GL_BLEND);
				}
				else if (map[y][x][z] == 2) {
					glColor4f(1.0, 0.5, 1.0, 0.5);
					glutSolidCube(10);
				}
				else if (map[y][x][z] == 3) {
					glColor4f(0.5, 0.0, 1.0, 0.5);
					glutSolidCube(10);
				}

				glTranslatef(0, 0, -10);
			}
			glTranslatef(10, 0, 110);
		}
		glTranslatef(-110, 10, 0);
	}
	glPopMatrix();

	// 게임 시간
	if (timeStage >= 0) {
		glLoadIdentity();
		int timeM{ (int)timeStage / 60 };
		int timeS{ (int)timeStage - timeM * 60 };
		char string[20];
		std::sprintf(string, "%d min %d second", timeM, timeS);

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(-125, 135);
		for (int i = 0; i < (int)strlen(string); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void Stage::updateStage(float elapsedTime)
{
	int num = cubetotalnum;
	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {

				if (map[y][x][z] == 3) // 제한 된 틀에 큐브가 있을 때
				{
					//PlaySound(TEXT(SOUND_FILE_NAME_CLEAR), NULL, SND_SYNC); // 일단 소리로 클리어 처리
					num--;
				}
			}
	
		}
	}
	if (num == 0 )
	{
		std::cout << " ok ";
	}

	// 게임 시간
	if (timeStage <= 0) {
		timeStage = 0;
	}
	else
		timeStage -= elapsedTime / 1000;
}

void Stage::Keyboard(unsigned char key)
{
	if (selectCube < numCube)
		if (cube[selectCube]->getType() == 0)
			cube[selectCube]->Keyboard(key);

	if (key == 'r') {
		int cnt[4]{ 0 };

		for (int y = 0; y < 11; ++y)
			for (int x = 0; x < 11; ++x)
				for (int z = 0; z < 11; ++z)
					if (cube[selectCube]->getCube(y, x, z) == 1) {
						if (map[y][x][z] == 0)
							cnt[0]++;
						else if (map[y][x][z] == 1)
							cnt[1]++;
						else if (map[y][x][z] == 2)
							cnt[2]++;
						else if (map[y][x][z] == 3)
							cnt[3]++;
					}

		int sum{ 0 };
		for (int i = 0; i < 4; ++i)
			sum += cnt[i];

		if (sum == cnt[0]) {
			setCubeType(1);

			for (int y = 0; y < 11; ++y)
				for (int x = 0; x < 11; ++x)
					for (int z = 0; z < 11; ++z)
						if (cube[selectCube]->getCube(y, x, z) == 1) {
							if (map[y][x][z] == 0)
								map[y][x][z] = 2;
						}
		}
		else if (sum == cnt[1]) {
			setCubeType(1);

			for (int y = 0; y < 11; ++y)
				for (int x = 0; x < 11; ++x)
					for (int z = 0; z < 11; ++z)
						if (cube[selectCube]->getCube(y, x, z) == 1) {
							if (map[y][x][z] == 1)
								map[y][x][z] = 3;
						}
		}
	}
	else if (key == 't') {
		setCubeType(0);

		for (int y = 0; y < 11; ++y)
			for (int x = 0; x < 11; ++x)
				for (int z = 0; z < 11; ++z)
					if (cube[selectCube]->getCube(y, x, z) == 1) {
						if (map[y][x][z] == 2)
							map[y][x][z] = 0;
						else if (map[y][x][z] == 3)
							map[y][x][z] = 1;
					}
	}
}

void Stage::Stage1()
{
	map[1][5][5] = 1;
	map[0][5][5] = 1;
	map[0][5][6] = 1;
	map[0][6][5] = 1;
	map[0][6][4] = 1;
	map[1][6][4] = 1;
	map[0][4][4] = 1;
	map[0][4][5] = 1;
	map[0][4][6] = 1;
	map[0][5][4] = 1;
	map[1][4][6] = 1;

	cubetotalnum = 11;

	for (int i = 0; i < numCube; ++i)
		cube[i] = new Cube(1, i);
}