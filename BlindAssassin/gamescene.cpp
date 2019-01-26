#include "OpenGLSB.h"
#include "Adding.h"
#include "SoundManager.h"
#include <malloc.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>

extern int cursorx, cursory; //마우스 커서
extern GLfloat windowWidth, windowHeight;
extern ActingUnit hero,hero_shuraken;
extern char buffer[10];
extern ActingUnit act_ary[100]; // 객체 배열
extern Unit unt_ary[100];
extern int u_num,a_num;
extern int myy, myx;
static int stagenum;
int disabled=0; // 죽인 적

clock_t sonar_start=0; // 소나
GLfloat ambientlight[]={0.0f,0.0f,0.0f,1.0f};

clock_t shuraken_start=0,shuraken_end=0; // 수리검

void keyfunc()
{
	if (GetAsyncKeyState(0x57) & 0x8000)//w
	{
		hero.unit.ypos++;
		TransformVertex(&hero);
		if(UnitCollision(hero,unt_ary,u_num))
			hero.unit.ypos--;
			myy = hero.unit.ypos;
	}	
			
	if (GetAsyncKeyState(0x41) & 0x8000)//a
	{		
		hero.unit.xpos--;
		TransformVertex(&hero);
		if(UnitCollision(hero,unt_ary,u_num))
			hero.unit.xpos++;
			myx = hero.unit.xpos;

	}
	if (GetAsyncKeyState(0x53) & 0x8000)//s
	{
		hero.unit.ypos--;
		TransformVertex(&hero);
		if(UnitCollision(hero,unt_ary,u_num))
			hero.unit.ypos++;
		myy = hero.unit.ypos;

	}
	if (GetAsyncKeyState(0x44) & 0x8000)//d
	{
		hero.unit.xpos++;
		TransformVertex(&hero);
		if(UnitCollision(hero,unt_ary,u_num))
			hero.unit.xpos--;
		myx = hero.unit.xpos;
	}
}

void Display2() {
	glClear(GL_COLOR_BUFFER_BIT);	
	keyfunc();
	
	
	TransformVertex(&hero);	// 좌표 변경
	for(int i=0;i<a_num;i++)
	{
		AIcompute(act_ary+i);
	}

	if(sonar_start!=0) // 소나 
	{
		sonarfunc();
	}

	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientlight);
	
	glColor3f(1.0f,1.0f,1.0f);	 // 정적 물체
	for(int i=0;i<u_num;i++)
	{
		DrawUnit(*(unt_ary+i));	
	}
	
	
	 // 적
	glDisable(GL_LIGHTING);
	glColor3f(1.0f,0.0f,0.0f);
	for(int i=0;i<a_num;i++)
	{
		DrawEnemy(*(act_ary+i));	
	}
	
	
	glColor3f(1.0f,1.0f,1.0f);
	DrawUnit(hero);	

	if(disabled<0)
	{
		initscene4();//패배
	}

	if(shuraken_start!=0) // 수리검
	{
		shurakenfunc();
		if(disabled==a_num)
		{
			Save(stagenum);
			SoundManager::sharedManager()->play(CLAP);
			initscene3();//승리
		}
	}


	glutSwapBuffers();
}

void mouseclick2(int button, int state, int x, int y) //마우스 입력 콜백 함수
{

	cursorx = (x - windowWidth / 2) / 4;
	cursory = (-1 * y + windowHeight / 2) / 4;

	if (state == GLUT_UP)
	{
		if((shuraken_start==0)&&(clock()-shuraken_end>2000))
		{
			shurakenmake(); // 수리검 던짐
		}
	}

}

void KeyBoard(unsigned char key, int x, int y)
{
	
	if(key=='Z'||key=='z') // 소나 발동
	{
		if(sonar_start==0)
		{
			sonar_start=clock();
			SoundManager::sharedManager()->play(SONAR_SOUND);
		}
	}
}


void initscene2(int stage)
{
	disabled=0;
	hero.unit.xpos=0;
	hero.unit.ypos=0;
	stagenum=stage;

	glutDisplayFunc(Display2);
	glutMouseFunc(mouseclick2);
	glutKeyboardFunc(KeyBoard);
	glEnable(GL_COLOR_MATERIAL);
	Load(stage);
	for(int i=0;i<u_num;i++)
	{
		TransformVertex(unt_ary+i);
	}
}

void sonarfunc()
{
	clock_t now=clock();
	float x=(float)(now-sonar_start)/1000;
	if(x<2)
	{
		*(ambientlight)=-1*pow(x,2.0f)+2*x;
		*(ambientlight+1)=-1*pow(x,2.0f)+2*x;
		*(ambientlight+2)=-1*pow(x,2.0f)+2*x;
	}
	else if(x>2)
	{
		*(ambientlight)=0;
		*(ambientlight+1)=0;
		*(ambientlight+2)=0;
	}
	if(x>5)
	{
		sonar_start=0;
	}
}

void shurakenmake() // 수리검 만듦
{
		shuraken_start=clock();
		float dx,dy,d;
		dx=cursorx-hero.unit.xpos;
		dy=cursory-hero.unit.ypos;
		d=sqrt(pow(dx,2.0f)+pow(dy,2.0f));
		hero_shuraken.vx=3*dx/d;
		hero_shuraken.vy=3*dy/d;
		hero_shuraken.unit.xpos=hero.unit.xpos;
		hero_shuraken.unit.ypos=hero.unit.ypos;
		SoundManager::sharedManager()->play(ATTACK_SOUND);
}

void shurakenfunc() // 수리검 충돌처리 등
{	
	TransformVertex(&hero_shuraken);
	if(UnitCollision(hero_shuraken,unt_ary,u_num)) // 벽에 부딪힘
	{
		shuraken_start=0;
		shuraken_end=clock();
	}
	else if(clock()-shuraken_start>3000) // 3초 이상 지나면 사라짐 (이거 나중에 없앰)
	{
		shuraken_start=0;
		shuraken_end=clock();
	}
	else if(ShurakenCollision(hero_shuraken,act_ary,a_num)) // 수리검이 적에게 맞음
	{
		disabled++;
		shuraken_start=0;
		shuraken_end=clock();
	}
	DrawUnit(hero_shuraken);
}
