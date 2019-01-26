#include "OpenGLSB.h"
#include "Adding.h"

#include <math.h>


static float Degree = 3.141592/180.0;
int u_num=0,a_num=0;


// 기본형

VertexList Circle={ // 12각 원
	12,
	{5,5*cos(30.0f*Degree),5*cos(60.0f*Degree),5*cos(90.0f*Degree),5*cos(120.0f*Degree),5*cos(150.0f*Degree),5*cos(180.0f*Degree),5*cos(210.0f*Degree),5*cos(240.0f*Degree),5*cos(270.0f*Degree),5*cos(300.0f*Degree),5*cos(330.0f*Degree)},
	{0,5*sin(30.0f*Degree),5*sin(60.0f*Degree),5*sin(90.0f*Degree),5*sin(120.0f*Degree),5*sin(150.0f*Degree),5*sin(180.0f*Degree),5*sin(210.0f*Degree),5*sin(240.0f*Degree),5*sin(270.0f*Degree),5*sin(300.0f*Degree),5*sin(330.0f*Degree)}
};

VertexList Rect= // 정사각형
{
	4,
	{-1,1,1,-1},
	{-1,-1,1,1}
};

VertexList Shuraken= // 수리검 모양
{
	8,
	{1,0.2,0,-0.2,-1,-0.2,0,0.2},
	{0,0.2,1,0.2,0,-0.2,-1,-0.2}
};

// 정적인 모형

Unit wall_1={
	-20,0,15,5,90,Rect
};

Unit wall_2={
	20,0,15,5,90,Rect
};

// 동적인 모형

ActingUnit flying={
	0,0,10,{0,0,5,5,0,Shuraken}
};

ActingUnit hero={ // 주인공 유닛
	0,0,0,{0,0,1,1,0,Circle}
};

ActingUnit hero_shuraken={ // 주인공 수리검
	0,0,25,{0,0,3,3,0,Shuraken}
};

ActingUnit awall_1=
{
	0,0,0,{0,25,15,5,0,Rect}
};

ActingUnit awall_2=
{
	0,0,0,{0,-25,15,5,0,Rect}
};


ActingUnit act_ary[100]={};
Unit unt_ary[100]={};
