#include<iostream>
#include"SoundManager.h"
#include<stdio.h>
#include "Adding.h"
using namespace std;
char buffer[10];

extern VertexList Circle,Rect,Shuraken;
extern int a_num,u_num;
extern ActingUnit act_ary[100];
extern Unit unt_ary[100];

void Save(int stage)
{
	if(stage==7)
	{
		for(int i=0;i<6;i++)
		{
			buffer[i]='0';
		}
	}
	else
	{
		buffer[stage-1] = '1';
	}

	FILE *save=fopen("save.txt", "wt");
	if(save==NULL){
		printf("파일 저장에 실패했습니다.\n");
	}
	fprintf(save, "%s", buffer);
	fclose(save);
	return;
}
void LoadBefore() //로드화면시 save.txt파일을 읽어옴
{
		 FILE *sFile = NULL;
		 sFile = fopen("save.txt", "r");
		 fscanf( sFile, "%s", buffer);
		 fclose( sFile);
}
int Load(int number) //해당스테이지객체정보 읽어옴
{   
	 FILE *pFile = NULL;

		switch(number)
		{
		case 1 :
			pFile = fopen("1.txt", "r" );
			SoundManager::sharedManager()->stop(START_SOUND);
			SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			SoundManager::sharedManager()->play(BACKGROUND_SOUND);
			break;
		case 2 :
			pFile = fopen("2.txt", "r" );
			SoundManager::sharedManager()->stop(START_SOUND);
			SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			SoundManager::sharedManager()->stop(BACKGROUND_SOUND);
			SoundManager::sharedManager()->play(BACKGROUND_SOUND);
			break;
		case 3 :
			pFile = fopen("3.txt", "r" );
			SoundManager::sharedManager()->stop(START_SOUND);
			SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			SoundManager::sharedManager()->stop(BACKGROUND_SOUND);
			SoundManager::sharedManager()->play(BACKGROUND_SOUND);
			break;
		case 4 :
			pFile = fopen("4.txt", "r" );
			SoundManager::sharedManager()->stop(START_SOUND);
			SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			SoundManager::sharedManager()->stop(BACKGROUND_SOUND);
			SoundManager::sharedManager()->play(BACKGROUND2_SOUND);
			break;
		case 5 :
		    pFile = fopen("5.txt", "r" );
			SoundManager::sharedManager()->stop(START_SOUND);
			SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			SoundManager::sharedManager()->stop(BACKGROUND2_SOUND);
			SoundManager::sharedManager()->play(BACKGROUND2_SOUND);
			break;
		case 6 :
			 pFile = fopen("6.txt", "r" );
			 SoundManager::sharedManager()->stop(START_SOUND); 
			 SoundManager::sharedManager()->stop(DEFEAT_SOUND);
			 SoundManager::sharedManager()->stop(BACKGROUND2_SOUND);
			 SoundManager::sharedManager()->play(BACKGROUND2_SOUND);
			 break;
		default :
			break;
	}
    if( pFile == NULL )
    {
       return -1;
    }
    else
    {
		int orgin;
        float xpos;
		float ypos;
		float xs;
		float ys;
		float rot;
		VertexList shape;
		u_num=0;
		a_num=0;
        while( !feof( pFile ) )
        {
            fscanf( pFile, "%f %f %f %f %f %d\n", &xpos, &ypos, &xs, &ys, &rot, &orgin);
			
			if(orgin<3) // 도형 등 사물
			{
				if(orgin==0)
					shape=Circle;
				else if(orgin==1)
					shape=Rect;
				else
					shape=Shuraken;
				(unt_ary+u_num)->xpos=xpos;
				(unt_ary+u_num)->ypos=ypos;
				(unt_ary+u_num)->xs=xs;
				(unt_ary+u_num)->ys=ys;
				(unt_ary+u_num)->rotation=rot;
				(unt_ary+u_num)->origin=shape;
				u_num++;
			}
			else // 적 위치
			{
				shape=Circle;
				(act_ary+a_num)->vx=0;
				(act_ary+a_num)->vy=0;
				(act_ary+a_num)->vrot=0;
				(act_ary+a_num)->unit.xpos=xpos;
				(act_ary+a_num)->unit.ypos=ypos;
				(act_ary+a_num)->unit.xs=xs;
				(act_ary+a_num)->unit.ys=ys;
				(act_ary+a_num)->unit.rotation=rot;
				(act_ary+a_num)->unit.origin=shape;
				a_num++;

			}
        }

        fclose( pFile );
		return 0;
    }
}