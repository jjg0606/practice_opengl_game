#include "SoundManager.h"
#include "fmod_errors.h"
#include <stdio.h>
#include <Windows.h>


const float DISTANCEFACTOR =3.28f;
extern int myx,myy;
extern int ex, ey;

SoundManager* SoundManager::instance;

SoundManager* SoundManager::sharedManager()
{
	if (instance == NULL) instance = new SoundManager;
	return instance;
}

void SoundManager::init()
{
	r = System_Create(&pFmod);
	ERRCHECK(r);
	r = pFmod->init(100, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(r);

}

void SoundManager::loading()
{
	r = pFmod->createSound("startmusic.mp3", FMOD_LOOP_NORMAL, NULL, &music[START_SOUND]);
	ERRCHECK(r);	
	r = pFmod->createSound("background.mp3", FMOD_LOOP_NORMAL, NULL, &music[BACKGROUND_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("background2.mp3", FMOD_LOOP_NORMAL, NULL, &music[BACKGROUND2_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("attack.mp3", FMOD_DEFAULT, NULL, &music[ATTACK_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("hit.mp3", FMOD_3D, NULL, &music[HIT_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("die.mp3", FMOD_DEFAULT, NULL, &music[DIE_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("sonar.mp3", FMOD_DEFAULT, NULL, &music[SONAR_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("defeat.mp3", FMOD_DEFAULT, NULL, &music[DEFEAT_SOUND]);
	ERRCHECK(r);
	r = pFmod->createSound("wrong.wav", FMOD_DEFAULT, NULL, &music[WRONG]);
	ERRCHECK(r);
	r = pFmod->createSound("clap.wav", FMOD_DEFAULT, NULL, &music[CLAP]);
	ERRCHECK(r);
	r = music[HIT_SOUND]->set3DMinMaxDistance(20.0f * DISTANCEFACTOR, 5000.0f *DISTANCEFACTOR);
	ERRCHECK(r);
	
	
}

void SoundManager::play(int _type)
{
	
	FMOD_VECTOR Cpos = {ex*DISTANCEFACTOR, ey*DISTANCEFACTOR, 0.0f};
	FMOD_VECTOR Cvel = {0.0f,0.0f,0.0f};
	
	
	pFmod->update();
	r = pFmod->playSound(FMOD_CHANNEL_FREE, music[_type], false, &ch[_type]);
	ERRCHECK(r);
	if(_type == HIT_SOUND)
	{
		r=ch[HIT_SOUND]->set3DAttributes(&Cpos, &Cvel);
		ERRCHECK(r);
	}
	
}

void SoundManager::stop(int _chNum)
{
	ch[_chNum]->stop();
}

void SoundManager::ERRCHECK(FMOD_RESULT _r)
{
	if (_r != FMOD_OK)
	{
		printf("FMOD error (%d) %s\n", _r, FMOD_ErrorString(_r));
		exit(-1);
	}
}

void SoundManager::sUpdate()
{	
	FMOD_VECTOR lis={myx * DISTANCEFACTOR, myy * DISTANCEFACTOR, 0.0f};


	FMOD_VECTOR vel={0.0f, 0.0f, 0.0f};
	FMOD_VECTOR up={0.0f, 0.0f, 1.0f};
	FMOD_VECTOR forward={0.0f, 1.0f, 0.0f};
	r= pFmod->set3DListenerAttributes(0,&lis,&vel,&forward,&up);
	ERRCHECK(r);
	pFmod->update();
}
