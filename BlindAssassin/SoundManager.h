#pragma once
#include "fmod.hpp"
#include "OpenGLSB.h"
using namespace FMOD;

enum SOUND {
	START_SOUND , BACKGROUND_SOUND, ATTACK_SOUND, HIT_SOUND, SONAR_SOUND, DIE_SOUND, BACKGROUND2_SOUND, DEFEAT_SOUND,WRONG,CLAP
};

class SoundManager {
public:

	static SoundManager* instance;
	static SoundManager* sharedManager();
	void init();
	void loading();
	void play(int _type);
	void stop(int _chNum);
	void ERRCHECK(FMOD_RESULT _r);
	void sUpdate();

private:
	System* pFmod;
	Channel* ch[10];
	Sound* music[10];
	FMOD_RESULT r;
};