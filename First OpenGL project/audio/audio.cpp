#include "audio.h"
#include <iostream>

Audio audio;

bool Audio::InitIrrKlang() {
	sound_engine = irrklang::createIrrKlangDevice();
	if (!sound_engine) {
		std::cerr << "Failed to Create Sound Engine.\n";
		return false;
	}
	else {
		std::cout << "Created Sound Device.\n";
		return true;
	}
}

void Audio::StartBGMusic() {
	if (sound_engine->play2D("Assets\\audio\\music.mp3", true));
}

void Audio::SetVolume(irrklang::ik_f32 volume) {
	sound_engine->setSoundVolume(volume);
}

void Audio::PlayAudio(std::string filename, bool playLooped, bool startPaused, bool track) {
	sound_engine->play2D(("Assets\\audio\\" + filename).c_str(), playLooped, startPaused, track);
}

void Audio::Mute() {
	sound_engine->setSoundVolume(0.0);
}