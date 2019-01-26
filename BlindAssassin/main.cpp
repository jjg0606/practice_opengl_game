#include "OpenGLSB.h"
#include "Adding.h"
#include "SoundManager.h"

#include <math.h>
#include <malloc.h>
#include <stdio.h>


/*========================== �������� ����====================================*/

GLfloat windowWidth; // 
GLfloat windowHeight; // 
int cursorx; // ���콺 X��ǥ
int cursory; // ���콺 Y��ǥ
int myx, myy;
int ex, ey;
float exs, eys;
int stagenumber=1; //�������� ��ȣ

/*==========================���� �Լ�====================================*/

int main(){
	SoundManager::sharedManager()->init();
	SoundManager::sharedManager()->loading();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000,800);
	glutCreateWindow("OpenGL");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutReshapeFunc(ChangeSize);		
	glutTimerFunc(17, TimerFunction, 1);
	 // 60fps	
	Initdisplay1();
	glutMainLoop();	
}

/*==========================�Լ� �����κ�====================================*/

void ChangeSize(GLsizei w,GLsizei h)
{
	if(h==0)
		h=1;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(w/-8, w/8, h/-8, h/8, 1.0, -1.0);
	windowHeight = h;
	windowWidth = w;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	SoundManager::sharedManager()->sUpdate();
	glutPostRedisplay(); // Redraw the scene with new coordinates
	glutTimerFunc(17, TimerFunction, 1);
}