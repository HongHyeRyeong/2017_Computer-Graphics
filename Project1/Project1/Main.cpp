#include <GL/glut.h>
#include <iostream>
#include "windows.h"
#include "Background.h"
#include "Stage.h"
#include "Menu.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

float traX, traY, traZ;
float rotX{ 30 }, rotY, rotZ;

bool left_button{ false }, grid{ false };
int mouseX, mouseY;

Background* bg;
Stage* stage;
Menu* menu;

DWORD g_startTime = NULL;

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
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	menu = new Menu();

	glutMainLoop();

	delete bg;
}

GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (menu == NULL) {
		glTranslatef(traX, traY, traZ);
		glRotatef(rotX, 1.0f, 0.0f, 0.0f);
		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

		DWORD currTime = timeGetTime();
		DWORD elapsedTime = currTime - g_startTime;
		g_startTime = currTime;

		if (stage->getStageType() == 2) {
			// Α¶Έν
			GLfloat AmbientLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat DiffuseLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat SpecularLight[4] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat lightPos[4] = { 0.0, 90.0, 0.0, 1.0 };
			GLfloat spotDir[3] = { 0.0, -1.0, 0.0 };

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
		}

		bg->updateBackground((float)elapsedTime);
		stage->updateStage((float)elapsedTime);

		if (stage->getStageType() != 1)
			bg->drawBackground();
		stage->drawStage();
	}
	else
		menu->drawMenu();

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

	if (menu == NULL) {
		if (key == 27) {
			if (stage->getStageType() != 0) {
				PlaySound(TEXT(SOUND_FILE_NAME_CUBE), NULL, SND_ASYNC);
				menu = new Menu();
				rotX = 30;
				rotY = 0;
				glDisable(GL_LIGHTING);
			}
		}
		else if (key == 'w') {
			if (selectNum > 0) {
				selectNum--;
				stage->setSelectCube(selectNum);
				PlaySound(TEXT(SOUND_FILE_NAME_CUBE), NULL, SND_ASYNC);
			}
		}
		else if (key == 'e') {
			if (selectNum < stage->getNumCube() - 1) {
				selectNum++;
				stage->setSelectCube(selectNum);
				PlaySound(TEXT(SOUND_FILE_NAME_CUBE), NULL, SND_ASYNC);
			}
		}
		else if (key == 'a' || key == 'z' || key == 's' || key == 'x' || key == 'd' || key == 'c' ||
			key == 'f' || key == 'g' || key == 'h' || key == 'r' || key == 't')
		{
			stage->Keyboard(key);
			PlaySound(TEXT(SOUND_FILE_NAME_CUBE), NULL, SND_ASYNC);
		}
		else if (key == 'u') {
			grid = !grid;
			bg->setGrid(grid);
			PlaySound(TEXT(SOUND_FILE_NAME_CUBE), NULL, SND_ASYNC);
		}
		else if (key == '1') {
			selectNum = 0;
			stage = new Stage(1);
		}
		else if (key == '2') {
			selectNum = 0;
			stage = new Stage(2);
		}
		else if (key == '3') {
			selectNum = 0;
			stage = new Stage(3);
		}
		else if (key == '4') {
			selectNum = 0;
			stage = new Stage(4);
		}
		else if (key == '5') {
			selectNum = 0;
			stage = new Stage(5);
		}
		else if (key == '6') {
			selectNum = 0;
			stage = new Stage(6);
		}
		else if (key == '7') {
			selectNum = 0;
			stage = new Stage(7);
		}
		else if (key == '8') {
			selectNum = 0;
			stage = new Stage(8);
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (menu != NULL) {
			delete menu;
			menu = NULL;

			g_startTime = timeGetTime();
			bg = new Background();
			stage = new Stage(1);
		}
		else {
			left_button = true;
			mouseX = x;
			mouseY = y;
		}
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
	glTranslatef(0.0, -20.0, -210.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}