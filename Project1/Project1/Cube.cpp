#include "Cube.h"

Cube::Cube(int numStage, int numCube) : numStage(numStage), numCube(numCube)
{
	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				cube[y][x][z] = 0;
	type = 0;

	if (numStage == 1)
		Stage1();
}

void Cube::drawCube()
{
	glPushMatrix();

	glColor3f(0.4, 0.8, 1.0);
	glTranslatef(-50, 5, 50);

	for (int y = 0; y < 11; ++y) {
		for (int x = 0; x < 11; ++x) {
			for (int z = 0; z < 11; ++z) {
				if (cube[y][x][z] == 1)
					glutSolidCube(10);

				glTranslatef(0, 0, -10);
			}
			glTranslatef(10, 0, 110);
		}
		glTranslatef(-110, 10, 0);
	}
	glPopMatrix();
}

void Cube::updateCube()
{

}

void Cube::Keyboard(unsigned char key)
{
	if (key == 'a' || key == 'z' || key == 's' || key == 'x' || key == 'd' || key == 'c')
		moveCube(key);
	else if (key == 'f' || key == 'g' || key == 'h')
		rotateCube(key);
}

void Cube::moveCube(unsigned char key)
{
	// 抗寇 贸府
	if (key == 'a') {
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				if (cube[i][10][j] == 1)
					return;
	}
	else if (key == 'z') {
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				if (cube[i][0][j] == 1)
					return;
	}
	else if (key == 's') {
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				if (cube[10][i][j] == 1)
					return;
	}
	else if (key == 'x') {
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				if (cube[0][i][j] == 1)
					return;
	}
	else if (key == 'd') {
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				if (cube[i][j][10] == 1)
					return;
	}
	else if (key == 'c') {
		for (int i = 0; i < 11; ++i)
			for (int j = 0; j < 11; ++j)
				if (cube[i][j][0] == 1)
					return;
	}

	int temp[11][11][11]{ 0 };

	if (key == 'a')
		centerCube[1]++;
	else if (key == 'z')
		centerCube[1]--;
	else if (key == 's')
		centerCube[0]++;
	else if (key == 'x')
		centerCube[0]--;
	else if (key == 'd')
		centerCube[2]++;
	else if (key == 'c')
		centerCube[2]--;

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (cube[y][x][z] == 1) {
					if (key == 'a')
						temp[y][x + 1][z] = 1;
					else if (key == 'z')
						temp[y][x - 1][z] = 1;
					else if (key == 's')
						temp[y + 1][x][z] = 1;
					else if (key == 'x')
						temp[y - 1][x][z] = 1;
					else if (key == 'd')
						temp[y][x][z + 1] = 1;
					else if (key == 'c')
						temp[y][x][z - 1] = 1;
				}

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				cube[y][x][z] = temp[y][x][z];
}

void Cube::rotateCube(unsigned char key)
{
	int temp[30][30][30]{ 0 };

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				if (cube[y][x][z] == 1) {
					if (key == 'f') {
						if (y == centerCube[0] && z == centerCube[2])
							temp[y + 10][x + 10][z + 10] = 1;
						else {
							int tempY{ 0 }, tempZ{ 0 };
							tempY = centerCube[0] - y;
							tempZ = z - centerCube[2];
							temp[centerCube[0] + tempZ + 10][x + 10][centerCube[2] + tempY + 10] = 1;
						}
					}
					else if (key == 'g') {
						if (x == centerCube[1] && z == centerCube[2])
							temp[y + 10][x + 10][z + 10] = 1;
						else {
							int tempX{ 0 }, tempZ{ 0 };
							tempX = centerCube[1] - x;
							tempZ = z - centerCube[2];
							temp[y + 10][centerCube[1] + tempZ + 10][centerCube[2] + tempX + 10] = 1;
						}
					}
					else if (key == 'h') {
						if (y == centerCube[0] && x == centerCube[1])
							temp[y + 10][x + 10][z + 10] = 1;
						else {
							int tempX{ 0 }, tempY{ 0 };
							tempX = centerCube[1] - x;
							tempY = y - centerCube[0];
							temp[centerCube[0] + tempX + 10][centerCube[1] + tempY + 10][z + 10] = 1;
						}
					}
				}

	// 抗寇 贸府
	int tempX{ 10 }, tempY{ 10 }, tempZ{ 10 };	// ++ -> --

	for (int x = 0; x < 30; ++x) {
		bool b{ false };

		for (int y = 0; y < 30; ++y) {
			for (int z = 0; z < 30; ++z)
				if (temp[y][x][z] == 1)
					if (x < 10 || x > 20) {
						b = true;
						break;
					}
			if (b)
				break;
		}

		if (b) {
			if (x < 10)
				tempX--;
			else if (x > 20)
				tempX++;
		}
	}

	for (int y = 0; y < 30; ++y) {
		bool b{ false };

		for (int x = 0; x < 30; ++x) {
			for (int z = 0; z < 30; ++z)
				if (temp[y][x][z] == 1)
					if (y < 10 || y > 20) {
						b = true;
						break;
					}
			if (b)
				break;
		}

		if (b) {
			if (y < 10)
				tempY--;
			else if (y > 20)
				tempY++;
		}
	}

	for (int z = 0; z < 30; ++z) {
		bool b{ false };

		for (int y = 0; y < 30; ++y) {
			for (int x = 0; x < 30; ++x)
				if (temp[y][x][z] == 1)
					if (z < 10 || z > 20) {
						b = true;
						break;
					}
			if (b)
				break;
		}

		if (b) {
			if (z < 10)
				tempZ--;
			else if (z > 20)
				tempZ++;
		}
	}

	for (int y = 0; y < 11; ++y)
		for (int x = 0; x < 11; ++x)
			for (int z = 0; z < 11; ++z)
				cube[y][x][z] = temp[y + tempY][x + tempX][z + tempZ];
}

void Cube::Stage1()
{
	if (numCube == 0) {
		centerCube[0] = 0;
		centerCube[1] = 2;
		centerCube[2] = 2;

		cube[0][2][2] = 1;
		cube[0][2][3] = 1;
		cube[0][3][2] = 1;
		cube[1][2][2] = 1;
	}
	else if (numCube == 1) {
		centerCube[0] = 0;
		centerCube[1] = 2;
		centerCube[2] = 1;

		cube[0][2][1] = 1;
		cube[0][2][2] = 1;
		cube[0][2][3] = 1;
		cube[0][3][1] = 1;
		cube[1][2][3] = 1;
	}
	else if (numCube == 2) {
		centerCube[0] = 0;
		centerCube[1] = 2;
		centerCube[2] = 2;

		cube[0][2][2] = 1;
		cube[1][2][2] = 1;
	}
}