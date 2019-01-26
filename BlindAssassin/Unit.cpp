#include "OpenGLSB.h"
#include "Adding.h"
#include <stdio.h>
#include "SoundManager.h"
#include <math.h>
static float Degree = 3.141592/180.0;

//ActingUnit.unit.rotation 의 값
#define DEAD 4.0f
#define HIGH 3.0f // 소음레벨 
#define MIDDLE 2.0f
#define LOW 1.0f

extern ActingUnit hero;
extern GLfloat ambientlight[];

extern Unit unt_ary[100];
extern int u_num;
extern int ex, ey; 
extern float exs, eys;
extern int disabled;

void DrawVertex(VertexList list) // 곧 없앰
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<list.n;i++)
	{
		glVertex2f(*(list.xpos+i), *(list.ypos+i));
	}
	glEnd();
}

void DrawUnit(Unit unit) // 유닛을 그리는 기능
{
	glBegin(GL_POLYGON);
	for(int i=0;i<unit.origin.n;i++)
	{
		glVertex2f(*(unit.transform.xpos+i),*(unit.transform.ypos+i));
	}
	glEnd();
}

void DrawUnit(ActingUnit acunit) // 유닛을 그리는 기능
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<acunit.unit.origin.n;i++)
	{
		glVertex2f(*(acunit.unit.transform.xpos+i),*(acunit.unit.transform.ypos+i));
	}
	glEnd();
}

void DrawUnit(ActingUnit *acunit) //유닛을 그리는 기능
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<acunit->unit.origin.n;i++)
	{
		glVertex2f(*(acunit->unit.transform.xpos+i),*(acunit->unit.transform.ypos+i));
	}
	glEnd();

}

void DrawEnemy(ActingUnit acunit) //적유닛을 그리는 기능
{
	if(acunit.unit.rotation==DEAD) //죽은 경우
		return;

	float dx,dy,d,color;
	dx=acunit.unit.xpos-hero.unit.xpos;
	dy=acunit.unit.ypos-hero.unit.ypos;
	d=sqrt(pow(dx,2.0f)+pow(dy,2.0f));
	
	if(d<15.0)
	{
		color=1.0f;
	}
	else if(d<30)
	{
		color=8/(d-7)+0.1*(acunit.unit.rotation);
	}
	else
	{
		color=0;
	}

	if(color<*(ambientlight))
		color=*(ambientlight);

	glColor3f(color,0.0f,0.0f);

	glBegin(GL_LINE_LOOP);
	for(int i=0;i<acunit.unit.origin.n;i++)
	{
		glVertex2f(*(acunit.unit.transform.xpos+i),*(acunit.unit.transform.ypos+i));
	}
	glEnd();
}

bool MinMaxTest(Unit unit1,Unit unit2) // Min Max 테스트 (충돌 안하면 false)
{
	float x1_min,x1_max,y1_min,y1_max;
	float x2_min,x2_max,y2_min,y2_max;
	float x,y;

	

	for(int i=0;i<unit1.origin.n;i++)
	{
		x=*(unit1.transform.xpos+i);
		y=*(unit1.transform.ypos+i);
		if(i==0)
		{
			x1_min=x;
			x1_max=x;
			y1_min=y;
			y1_max=y;
		}
		else
		{
			if(x>x1_max)
				x1_max=x;
			else if(x<x1_min)
				x1_min=x;

			if(y>y1_max)
				y1_max=y;
			else if(y<y1_min)
				y1_min=y;
		}
	}

	for(int i=0;i<unit2.origin.n;i++)
	{
		x=*(unit2.transform.xpos+i);
		y=*(unit2.transform.ypos+i);
		if(i==0)
		{
			x2_min=x;
			x2_max=x;
			y2_min=y;
			y2_max=y;
		}
		else
		{
			if(x>x2_max)
				x2_max=x;
			else if(x<x2_min)
				x2_min=x;

			if(y>y2_max)
				y2_max=y;
			else if(y<y2_min)
				y2_min=y;
		}
	}
	
	if((x1_max<x2_min)||(x1_min>x2_max)||(y1_max<y2_min)||(y1_min>y2_max)) //충돌 안함
		return false;

	return true;
}

bool ContainTest(Unit unit1,Unit unit2) // 포함 테스트 (포함 하면 true)
{
	float p1[2],p2[2],p3[2];
	float anglesum;

	for(int i=0;i<unit2.origin.n;i++)
	{
		p1[0]=*(unit2.transform.xpos+i);
		p1[1]=*(unit2.transform.ypos+i);
		anglesum=0;
		for(int j=0;j<unit1.origin.n;j++)
		{
			p2[0]=*(unit1.transform.xpos+j);
			p2[1]=*(unit1.transform.ypos+j);
			p3[0]=*(unit1.transform.xpos+(j+1)%unit1.origin.n);
			p3[1]=*(unit1.transform.ypos+(j+1)%unit1.origin.n);
			anglesum=anglesum+InerAngle(p1,p2,p3);
		}
		if(anglesum>=359)
			return true;
	}

	return false;
}

bool CollisionTest(Unit unit1,Unit unit2) // MinMax와 ContainTest를 하여 충돌 하는지 안하는지 판정
{
	if(MinMaxTest(unit1,unit2)==true)
	{
		if(ContainTest(unit1,unit2)==false)
			return ContainTest(unit2,unit1);
		else
			return true;
	}
	else
		return false;
}

bool UnitCollision(ActingUnit act,Unit* ary,int num)
{
	for(int i=0;i<num;i++)
	{
		if(CollisionTest(act.unit,*(ary+i))==true)
			return true;
	}
	return false;
};

bool UnitCollision(ActingUnit act,ActingUnit* ary,int num)
{
	for(int i=0;i<num;i++)
	{
		if(CollisionTest(act.unit,(ary+i)->unit)==true)
			return true;
	}
	return false;
};

bool ShurakenCollision(ActingUnit act,ActingUnit* ary,int num)
{
	for(int i=0;i<num;i++)
	{
		if((ary+i)->unit.rotation!=DEAD) // 죽은애가 아님
		{
			if(CollisionTest(act.unit,(ary+i)->unit)==true)
			{
				(ary+i)->unit.rotation=DEAD;//죽임
				//(ary+i)->unit.xpos 죽은애 X좌표
				ex = (ary + i)->unit.xpos;
				//(ary+i)->unit.ypos 죽은애 Y좌표
				ey = (ary + i)->unit.ypos;
				//hero.unit.xpos 주인공 X좌표
				//hero.unit.ypos 주인공 Y좌표
				SoundManager::sharedManager()->play(HIT_SOUND);
				
				return true;
			}
		}
	}
	return false;
};

float InerAngle(float* p1,float* p2,float* p3) // 점의 사잇각 (각 p2-p1-p3) 를 리턴함
{
	float vector1[2]={*(p2)-*(p1),*(p2+1)-*(p1+1)};
	float vector2[2]={*(p3)-*(p1),*(p3+1)-*(p1+1)};

	float l1,l2,l,ip;
	l1=sqrt(pow(vector1[0],2)+pow(vector1[1],2));
	l2=sqrt(pow(vector2[0],2)+pow(vector2[1],2));
	l=l1*l2;
	ip=vector1[0]*vector2[0]+vector1[1]*vector2[1];
	return acos(ip/l)/Degree;
}

void TransformVertex(Unit *unit) // 유닛의 변환 이후 좌표를 만들어 주는 함수
{
	float matrix[4]={
		unit->xs*cos(unit->rotation*Degree),unit->xs*sin(unit->rotation*Degree),
		unit->ys*(-1)*sin(unit->rotation*Degree),unit->ys*cos(unit->rotation*Degree)
	};

	for(int i=0;i<unit->origin.n;i++)
	{
		float x=*(unit->origin.xpos+i);
		float y=*(unit->origin.ypos+i);
		
		*(unit->transform.xpos+i)=x*matrix[0]+y*matrix[2]+unit->xpos;
		*(unit->transform.ypos+i)=x*matrix[1]+y*matrix[3]+unit->ypos;
	}
}

void TransformVertex(ActingUnit *actunit) // 움직이는 유닛의 좌표를 만들어 주는 함수
{
	actunit->unit.xpos=actunit->unit.xpos+actunit->vx;
	actunit->unit.ypos=actunit->unit.ypos+actunit->vy;
	actunit->unit.rotation=actunit->unit.rotation+actunit->vrot;

	float matrix[4]={
		actunit->unit.xs*cos(actunit->unit.rotation*Degree),actunit->unit.xs*sin(actunit->unit.rotation*Degree),
		actunit->unit.ys*(-1)*sin(actunit->unit.rotation*Degree),actunit->unit.ys*cos(actunit->unit.rotation*Degree)
	};

	for(int i=0;i<actunit->unit.origin.n;i++)
	{
		float x=*(actunit->unit.origin.xpos+i);
		float y=*(actunit->unit.origin.ypos+i);
		
		*(actunit->unit.transform.xpos+i)=x*matrix[0]+y*matrix[2]+actunit->unit.xpos;
		*(actunit->unit.transform.ypos+i)=x*matrix[1]+y*matrix[3]+actunit->unit.ypos;
	}
}
void AIcompute(ActingUnit *actunit) // 인공지능
{
   if(actunit->unit.rotation==DEAD)
      return;

   float p1[2]={actunit->unit.xpos,actunit->unit.ypos};
   float p2[2]={hero.unit.xpos,hero.unit.ypos};
   bool sight=false;

   float dx=hero.unit.xpos-actunit->unit.xpos;
   float dy=hero.unit.ypos-actunit->unit.ypos;
   float d=sqrt(pow(dx,2.0f)+pow(dy,2.0f));
   
   if(d<11)
   {
      disabled=-1;//패배조건
	  SoundManager::sharedManager()->stop(0);
	  SoundManager::sharedManager()->stop(1);
	  SoundManager::sharedManager()->stop(6);
      SoundManager::sharedManager()->play(DIE_SOUND);
	  //SoundManager::sharedManager()->stop(BACKGROUND2_SOUND);
	  //SoundManager::sharedManager()->stop(BACKGROUND_SOUND);
	  SoundManager::sharedManager()->play(DEFEAT_SOUND);

   }

   for(int i=0;i<u_num;i++)
   {
      if(Sight2(p1,p2,*(unt_ary+i))==true)
      {
         sight=true;
         break;
      }
   }
   if(sight==true) // 눈에 안 보임
   {
      actunit->vx=0;
      actunit->vy=0;
      TransformVertex(actunit);
      if(UnitCollision(*actunit,unt_ary,u_num))
      {
         actunit->vx=0.9*actunit->vx;
         actunit->vy=0.9*actunit->vy;
         TransformVertex(actunit);
         if(UnitCollision(*actunit,unt_ary,u_num))
         {
         actunit->vx=0;
         actunit->vy=0;
         actunit->unit.xpos=actunit->unit.xpos-actunit->vx;
         actunit->unit.ypos=actunit->unit.ypos-actunit->vy;
         TransformVertex(actunit);
         }
      }
      return;
   }
   //눈에 보임


   if(d>70) // 인식 못하는 거리
   {
      actunit->vx=0;
      actunit->vy=0;
      TransformVertex(actunit);
      if(UnitCollision(*actunit,unt_ary,u_num))
      {
         actunit->vx=0;
         actunit->vy=0;
         actunit->unit.xpos=actunit->unit.xpos-0.5*dx/d;
         actunit->unit.ypos=actunit->unit.ypos-0.5*dy/d;
         TransformVertex(actunit);
      }
   }
   else if(d>30) // 천천히 달려옴
   {         
      actunit->unit.rotation==MIDDLE;
      actunit->vx=0.5*dx/d;
      actunit->vy=0.5*dy/d;
      TransformVertex(actunit);
      if(UnitCollision(*actunit,unt_ary,u_num))
      {
         actunit->vx=0;
         actunit->vy=0;
         actunit->unit.xpos=actunit->unit.xpos-0.5*dx/d;
         actunit->unit.ypos=actunit->unit.ypos-0.5*dy/d;
         TransformVertex(actunit);
      }

   }
   else if(d>11) // 빠르게 달려옴
   {
      actunit->unit.rotation==HIGH;
      actunit->vx=1*dx/d;
      actunit->vy=1*dy/d;
      TransformVertex(actunit);
      if(UnitCollision(*actunit,unt_ary,u_num))
      {
         actunit->vx=0;
         actunit->vy=0;
         actunit->unit.xpos=actunit->unit.xpos-1*dx/d;
         actunit->unit.ypos=actunit->unit.ypos-1*dy/d;
         TransformVertex(actunit);
      }

   }

}

bool Sight(float* p1,float* p2,float* p3,float* p4) // 선분 p1-p2 와 p3-p4 사이에 교점을 찾음
{
	float x01=*(p1),y01=*(p1+1);
	float x02=*(p2),y02=*(p2+1);
	float x11=*(p3),y11=*(p3+1);
	float x12=*(p4),y12=*(p4+1);

	float a0,b0,c0;
	float a1,b1,c1;
	float D;

	a0=y01-y02;
	b0=x02-x01;
	c0=x01*y02-y01*x02;

	a1=y11-y12;
	b1=x12-x11;
	c1=x11*y12-y11*x12;
	D=a0*b1-b0*a1;

	if(D==0)
	{
	if((a0/a1)==(c0/c1)) // 같은 직선
		return true;

	return false; // 평행한 경우
	}

	float xa,ya;
	xa=(-1*b1*c0+b0*c1)/D;
	ya=(a1*c0-a0*c1)/D;

	if((xa>max(x01,x02))||(xa<min(x01,x02))||(ya>max(y01,y02))||(ya<min(y01,y02))||(xa>max(x11,x12))||(xa<min(x11,x12))||(ya>max(y11,y12))||(ya<min(y11,y12)))
		return false;

	return true;
}

bool Sight2(float* p1,float* p2,Unit unit)
{
	float p3[2],p4[2];
	int n=unit.origin.n;
	for(int i=0;i<n;i++)
	{
		p3[0]=*(unit.transform.xpos+i);
		p3[1]=*(unit.transform.ypos+i);
		p4[0]=*(unit.transform.xpos+(i+1)%n);
		p4[1]=*(unit.transform.ypos+(i+1)%n);
		if(Sight(p1,p2,p3,p4))
			return true;
	}
	return false;
}
