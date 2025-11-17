#pragma once
#include "../includes/IrrKlang/irrKlang.h"
#include <string>
#include <vector>

struct Audio {
public:
	bool InitIrrKlang();
	void StartBGMusic();
	void SetVolume(irrklang::ik_f32 volume);
	void PlayAudio(std::string filename, bool playLooped, bool startPaused, bool track);
	void Mute();

	bool mute;
	irrklang::ISoundEngine* sound_engine;

private:
	irrklang::ik_f32 volume;

};

extern Audio audio;