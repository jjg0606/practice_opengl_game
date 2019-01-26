// 시작화면 출력과 관련된 함수
#include "OpenGLSB.h"
#include "Adding.h"
#include "SoundManager.h"
#include <malloc.h>
#include <stdio.h>

extern int cursorx, cursory;
extern GLfloat windowWidth, windowHeight;
extern char buffer[10];
static ImageLoad i1, i2, i3,i4;

void displayStartScene()
{
	glRasterPos2f(i1.iWidth / -8, 0);
	glDrawPixels(i1.iWidth, i1.iHeight, i1.eFormat, GL_UNSIGNED_BYTE, i1.image);

	glRasterPos2f(i2.iWidth / -8, -40);
	glDrawPixels(i2.iWidth, i2.iHeight, i2.eFormat, GL_UNSIGNED_BYTE, i2.image);

	glRasterPos2f(i3.iWidth / -8, -80);
	glDrawPixels(i3.iWidth, i3.iHeight, i3.eFormat, GL_UNSIGNED_BYTE, i3.image);

	glRasterPos2f(i4.iWidth / -8, 35);
	glDrawPixels(i4.iWidth, i4.iHeight, i4.eFormat, GL_UNSIGNED_BYTE, i4.image);
}

int startscene_menuidentify()
{
	if ((cursorx > i1.iWidth / -8) && (cursorx < i1.iWidth / 8) && (cursory > 0) && (cursory < i1.iHeight / 4))
	{
		
		
		return 1;
		
	}
	if ((cursorx > i2.iWidth / -8) && (cursorx < i2.iWidth / 8) && (cursory > -40) && (cursory < -40 + i2.iHeight / 4))
	{
		
		return 2;
		
	}
	if ((cursorx > i3.iWidth / -8) && (cursorx < i3.iWidth / 8) && (cursory > -80) && (cursory < -80 + i3.iHeight / 4))
		return 3;

	return 0;
}

void mouseclick1(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
	{
		cursorx = (x - windowWidth / 2) / 4;
		cursory = (-1 * y + windowHeight / 2) / 4;

		int selection = startscene_menuidentify();

		if (selection == 1) //게임 시작
		{			
			Save(7);
			initscene2(1);
			return;
		}
		if (selection == 2) // 게임 로드
		{
			initscene3();
			return;
		}
		if (selection == 3)
		{
			free(i1.image);
			free(i2.image);
			free(i3.image);
			free(i4.image);
			exit(0);
		}
	}
}

void Display1() {
	glClear(GL_COLOR_BUFFER_BIT);

	displayStartScene();


	glutSwapBuffers();
}

void Initdisplay1()
{
	glutMouseFunc(mouseclick1);
	glutDisplayFunc(Display1);
	SoundManager::sharedManager()->stop(0);
	SoundManager::sharedManager()->stop(1);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	i1.image = gltLoadTGA("Image/GameStart.tga", &i1.iWidth, &i1.iHeight, &i1.iComponents, &i1.eFormat);
	i2.image = gltLoadTGA("Image/load.tga", &i2.iWidth, &i2.iHeight, &i2.iComponents, &i2.eFormat);
	i3.image = gltLoadTGA("Image/gameend.tga", &i3.iWidth, &i3.iHeight, &i3.iComponents, &i3.eFormat);
	i4.image = gltLoadTGA("Image/Title.tga", &i4.iWidth, &i4.iHeight, &i4.iComponents, &i4.eFormat);

	SoundManager::sharedManager()->play(START_SOUND);
};