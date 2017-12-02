#include <GL/glut.h>
#include <iostream>
#include "Background.h"
#include "Stage.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);

float traX, traY, traZ;
float rotX{ 30 }, rotY, rotZ;

Background* bg;
Stage* stage;

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
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunction, 1);

	glEnable(GL_DEPTH_TEST);

	bg = new Background();
	stage = new Stage(1);

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

	bg->drawBackground();
	stage->drawStage();

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	bg->updateBackground();
	stage->updateStage();

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
	else if (key == 'y')
		rotY += 10;
	else if (key == 'u')
		bg->setGrid(true);
	else if (key == 'U')
		bg->setGrid(false);
	else if (key == 'i') {
		rotY = 0;
	}
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(5.0, -20.0, -200.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}