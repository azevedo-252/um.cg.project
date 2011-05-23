/**
 * Sound.cpp
 */

#include <string.h>
#include <iostream>

using namespace std;

#include "Sound.h"
#include "externs.h"

string Sound::sounds_path;
SOUND Sound::sounds[SOUND_COUNT];
bool Sound::music_playing;
bool Sound::on;

void Sound::load() {
	on = conf.rint("sound:on") == 1;
	sounds_path = conf.rstring("resources:sounds_path");


	// a musica principal e carregada e definida para tocar em looping
	Sound::loadSingle(SOUND_MAIN, conf.rstring("sound:main_music"));
	alSourcei(sounds[SOUND_MAIN].source, AL_LOOPING, AL_TRUE);

	Sound::loadSingle(SOUND_WIN, conf.rstring("sound:win_music"));
	alSourcei(sounds[SOUND_WIN].source, AL_LOOPING, AL_FALSE);

	Sound::loadSingle(SOUND_KEY_CATCH, conf.rstring("sound:key_catch"));
	alSourcei(sounds[SOUND_KEY_CATCH].source, AL_LOOPING, AL_FALSE);
	
	Sound::loadSingle(SOUND_LIFE_LOST, conf.rstring("sound:life_lost"));
	alSourcei(sounds[SOUND_LIFE_LOST].source, AL_LOOPING, AL_FALSE);

	Sound::loadSingle(SOUND_JUMP, conf.rstring("sound:jump"));
	alSourcei(sounds[SOUND_JUMP].source, AL_LOOPING, AL_FALSE);

	Sound::loadSingle(SOUND_GAME_OVER, conf.rstring("sound:game_over"));
	alSourcei(sounds[SOUND_GAME_OVER].source, AL_LOOPING, AL_FALSE);

	music_playing = true;
}

void Sound::loadSingle(SOUND_TYPE id, string path) {
	string file_path(sounds_path);
	file_path.append(path);

	sounds[id].buffer = alutCreateBufferFromFile(file_path.c_str());
	alGenSources(1, &(sounds[id].source));
	alSourcei(sounds[id].source, AL_BUFFER, sounds[id].buffer);
}

void Sound::play(SOUND_TYPE id) {
	if (InputManager::getOpState(SOUND_MODE) == KEY_ON)
		alSourcePlay(sounds[id].source);
}

void Sound::stop(SOUND_TYPE id) {
	alSourceStop(sounds[id].source);
}

void Sound::toogleMusic() {
	if (InputManager::getOpState(MUSIC_MODE) == KEY_ON) {
		Sound::stop(SOUND_MAIN);
		music_playing = false;
	} else {
		Sound::play(SOUND_MAIN);
		music_playing = true;
	}
}

void Sound::toogleSounds() {
	on = !on;
}