#include <GL/glut.h>
#include <iostream>
#include "windows.h"
#include "Background.h"
#include "Stage.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

float traX, traY, traZ;
float rotX{ 30 }, rotY, rotZ;

bool left_button{ false };
int mouseX, mouseY;

Background* bg;
Stage* stage;

DWORD g_startTime = NULL;
DWORD g_bulletTime = NULL;

int selectNum;

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CubeSpace");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunction, 1);

	glEnable(GL_DEPTH_TEST);

	bg = new Background();
	stage = new Stage(1);
	g_startTime = timeGetTime();

	glutMainLoop();

	delete bg;
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(traX, traY, traZ);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_startTime;
	g_startTime = currTime;

	bg->updateBackground((float)elapsedTime);
	stage->updateStage((float)elapsedTime);

	bg->drawBackground();
	stage->drawStage();

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		exit(0);
	else if (key == 'w') {
		if (selectNum > 0) {
			selectNum--;
			stage->setSelectCube(selectNum);
		}
	}
	else if (key == 'e') {
		if (selectNum < stage->getNumCube() - 1) {
			selectNum++;
			stage->setSelectCube(selectNum);
		}
	}
	else if (key == 'r')
		stage->setCubeType(1);
	else if (key == 't')
		stage->setCubeType(0);
	else if (key == 'a' || key == 'z' || key == 's' || key == 'x' || key == 'd' || key == 'c'||
		key == 'f' || key == 'g' || key == 'h')
		stage->Keyboard(key);
	else if (key == 'u')
		bg->setGrid(true);
	else if (key == 'U')
		bg->setGrid(false);
	else if (key == 'i') {
		rotX = 30;
		rotY = 0;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		left_button = true;
		mouseX = x;
		mouseY = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		left_button = false;
}

void Motion(int x, int y)
{
	if (left_button == true) {

		if (mouseX > x)
			rotY--;
		else if (mouseX < x)
			rotY++;

		if (mouseY > y)
			rotX--;
		else if (mouseY < y)
			rotX++;

		mouseX = x;
		mouseY = y;
	}
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 4000.0);
	glTranslatef(0.0, -20.0, -230.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}