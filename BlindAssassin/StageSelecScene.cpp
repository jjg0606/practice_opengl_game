#include "Adding.h"
#include "OpenGLSB.h"
#include "SoundManager.h"
#include <malloc.h>
#include <stdio.h>

extern int cursorx, cursory; //마우스 커서
extern GLfloat windowWidth, windowHeight;
static ImageLoad i1,c1,c2,c3,c4,c5,c6;
extern char buffer[10];


void initscene3()
{
	LoadBefore();
	glutDisplayFunc(Display3);
	glutMouseFunc(mouseclick3);
	glutKeyboardFunc(KeyBoard2);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	i1.image = gltLoadTGA("Image/SelectStage.tga", &i1.iWidth, &i1.iHeight, &i1.iComponents, &i1.eFormat);
	c1.image = gltLoadTGA("Image/stage/icon1.tga", &c1.iWidth, &c1.iHeight, &c1.iComponents, &c1.eFormat);
	c2.image = gltLoadTGA("Image/stage/icon2.tga", &c2.iWidth, &c2.iHeight, &c2.iComponents, &c2.eFormat);
	c3.image = gltLoadTGA("Image/stage/icon3.tga", &c3.iWidth, &c3.iHeight, &c3.iComponents, &c3.eFormat);
	c4.image = gltLoadTGA("Image/stage/icon4.tga", &c4.iWidth, &c4.iHeight, &c4.iComponents, &c4.eFormat);
	c5.image = gltLoadTGA("Image/stage/icon5.tga", &c5.iWidth, &c5.iHeight, &c5.iComponents, &c5.eFormat);
	c6.image = gltLoadTGA("Image/stage/icon6.tga", &c6.iWidth, &c6.iHeight, &c6.iComponents, &c6.eFormat);
}

void mouseclick3(int button, int state, int x, int y) //마우스 입력 콜백 함수
{

	cursorx = (x - windowWidth / 2) / 4;
	cursory = (-1 * y + windowHeight / 2) / 4;

	if (state == GLUT_UP)
	{

		if(Icon(cursorx,cursory,c1.iWidth / -8, 20,c1.iWidth,c1.iHeight))
		{			
			if(buffer[0]=='1')
				SoundManager::sharedManager()->play(WRONG);
			else
				initscene2(1);
			
		}
		if(Icon(cursorx,cursory,40, -10,c2.iWidth,c2.iHeight))
		{
			
			if(buffer[1]=='1')
				SoundManager::sharedManager()->play(WRONG);
			else
				initscene2(2);
			
		}
		if(Icon(cursorx,cursory,40, -40,c3.iWidth,c3.iHeight))
		{
			if(buffer[2]=='1')
				SoundManager::sharedManager()->play(WRONG);
			else
				initscene2(3);
			
		}
		if(Icon(cursorx,cursory,c4.iWidth/-8, -70,c3.iWidth,c3.iHeight))
		{
			if((buffer[3]=='1')||(buffer[0]!='1')||(buffer[1]!='1')||(buffer[2]!='1'))
				SoundManager::sharedManager()->play(WRONG);
			else
				initscene2(4);
			
		}
		if(Icon(cursorx,cursory,-40-c5.iWidth/4, -40,c3.iWidth,c3.iHeight))
		{
			if((buffer[4]=='1')||(buffer[0]!='1')||(buffer[1]!='1')||(buffer[2]!='1'))
				SoundManager::sharedManager()->play(WRONG);
			else
				initscene2(5);
			
		}
		if(Icon(cursorx,cursory,-40-c6.iWidth/4, -10,c3.iWidth,c3.iHeight))
		{
			if((buffer[5]=='1')||(buffer[0]!='1')||(buffer[1]!='1')||(buffer[2]!='1'))
				SoundManager::sharedManager()->play(WRONG);
			else
				initscene2(6);
			
		}
	}

}

void KeyBoard2(unsigned char key, int x, int y)
{
}

void Display3()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2f(i1.iWidth / -8, 60);
	glDrawPixels(i1.iWidth, i1.iHeight, i1.eFormat, GL_UNSIGNED_BYTE, i1.image);

	glRasterPos2f(c1.iWidth / -8, 20);
	glDrawPixels(c1.iWidth, c1.iHeight, c1.eFormat, GL_UNSIGNED_BYTE, c1.image);

	glRasterPos2f(40, -10);
	glDrawPixels(c2.iWidth, c2.iHeight, c2.eFormat, GL_UNSIGNED_BYTE, c2.image);

	glRasterPos2f(40, -40);
	glDrawPixels(c3.iWidth, c3.iHeight, c3.eFormat, GL_UNSIGNED_BYTE, c3.image);

	glRasterPos2f(c4.iWidth/-8, -70);
	glDrawPixels(c4.iWidth, c4.iHeight, c4.eFormat, GL_UNSIGNED_BYTE, c4.image);

	glRasterPos2f(-40-c5.iWidth/4, -40);
	glDrawPixels(c5.iWidth, c5.iHeight, c5.eFormat, GL_UNSIGNED_BYTE, c5.image);

	glRasterPos2f(-40-c6.iWidth/4, -10);
	glDrawPixels(c6.iWidth, c6.iHeight, c6.eFormat, GL_UNSIGNED_BYTE, c6.image);


	glutSwapBuffers();
}

bool Icon(float x,float y,float rasterx,float rastery,float width,float height) // 포함을 이용한 메뉴 클릭 함수
{
	float cursor[2]={x,y};
	float p1[2]={rasterx,rastery};
	float p2[2]={rasterx+width/4,rastery};
	float p3[2]={rasterx+width/4,rastery+height/4};
	float p4[2]={rasterx,rastery+height/4};
	float anglesum=0;

	anglesum+=InerAngle(cursor,p1,p2);
	anglesum+=InerAngle(cursor,p2,p3);
	anglesum+=InerAngle(cursor,p3,p4);
	anglesum+=InerAngle(cursor,p4,p1);

	if(anglesum>359)
		return true;

	return false;

}
// YOU DIED 씬
static ImageLoad m1, m2, m3;
void initscene4()
{
	glutDisplayFunc(Display4);
	glutMouseFunc(mouseclick4);
	glutKeyboardFunc(KeyBoard2);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	m1.image = gltLoadTGA("Image/dead.tga", &m1.iWidth, &m1.iHeight, &m1.iComponents, &m1.eFormat);
	m2.image = gltLoadTGA("Image/continue.tga", &m2.iWidth, &m2.iHeight, &m2.iComponents, &m2.eFormat);
	m3.image = gltLoadTGA("Image/exit.tga", &m3.iWidth, &m3.iHeight, &m3.iComponents, &m3.eFormat);
}

void mouseclick4(int button, int state, int x, int y) //마우스 입력 콜백 함수
{
	cursorx = (x - windowWidth / 2) / 4;
	cursory = (-1 * y + windowHeight / 2) / 4;
	if (state == GLUT_UP)
	{
		if (Icon(cursorx, cursory, m2.iWidth / -8, -20, m2.iWidth, m2.iHeight))
			initscene3();
		if (Icon(cursorx, cursory, m3.iWidth / -8, -70, m3.iWidth, m3.iHeight))
		{
			SoundManager::sharedManager()->stop(BACKGROUND2_SOUND);
			SoundManager::sharedManager()->stop(BACKGROUND_SOUND);
			SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			SoundManager::sharedManager()->play(START_SOUND);
			Initdisplay1();
		}
	}
}

void Display4()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2f(m1.iWidth / -8, 40);
	glDrawPixels(m1.iWidth, m1.iHeight, m1.eFormat, GL_UNSIGNED_BYTE, m1.image);
	glRasterPos2f(m2.iWidth / -8, -20);
	glDrawPixels(m2.iWidth, m2.iHeight, m2.eFormat, GL_UNSIGNED_BYTE, m2.image);
	glRasterPos2f(m3.iWidth / -8, -70);
	glDrawPixels(m3.iWidth, m3.iHeight, m3.eFormat, GL_UNSIGNED_BYTE, m3.image);
	glutSwapBuffers();

}