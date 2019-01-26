#include "OpenGLSB.h"
#include "Adding.h"
#include "SoundManager.h"

#include <math.h>
#include <malloc.h>
#include <stdio.h>


/*========================== 전역변수 선언====================================*/

GLfloat windowWidth; // 
GLfloat windowHeight; // 
int cursorx; // 마우스 X좌표
int cursory; // 마우스 Y좌표
int myx, myy;
int ex, ey;
float exs, eys;
int stagenumber=1; //스테이지 번호

/*==========================메인 함수====================================*/

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

/*==========================함수 구현부분====================================*/

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