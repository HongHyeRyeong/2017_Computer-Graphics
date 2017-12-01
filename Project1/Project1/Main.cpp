#include <GL/glut.h>
#include <iostream>
#include "Background.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);

float traX, traY, traZ;
float rotX{ 30 }, rotY, rotZ;

Background* bg;

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

	bg->updateBackground();
	bg->drawBackground();

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
	else if (key == 'a')
		traX -= 10;
	else if (key == 'd')
		traX += 10;
	else if (key == 'w')
		traY += 10;
	else if (key == 's')
		traY -= 10;
	else if (key == '+')
		traZ += 10;
	else if (key == '-')
		traZ -= 10;
	else if (key == 'x')
		rotX += 10;
	else if (key == 'y')
		rotY += 10;
	else if (key == 'z')
		rotZ += 10;
	else if (key == 'i') {
		traX = 0;
		traY = 0;
		traZ = 0;
		rotX = 30;
		rotY = 0;
		rotZ = 0;
	}
	else if (key == 'g')
		bg->setGrid(true);
	else if (key == 'G')
		bg->setGrid(false);
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(5.0, -20.0, -300.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}