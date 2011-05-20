/**
 * Sound.h
 */

#ifndef _SOUND_H
#define _SOUND_H

#include <iostream>
#include <AL/al.h>
#include <AL/alut.h>

using namespace std;

typedef enum e_sounds {
    SOUND_MAIN,
    SOUND_WIN,
    SOUND_JUMP,
    SOUND_KEY_CATCH,
    SOUND_LIFE_LOST,
    SOUND_GAME_OVER,
    SOUND_COUNT,
} SOUND_TYPE;

typedef struct s_sound {
    ALuint buffer, source;
} SOUND;

class Sound {
public:
    static string sounds_path;
    static SOUND sounds[];

    static void load();
    static void loadSingle(SOUND_TYPE id, string path);

    static void play(SOUND_TYPE id);
    static void stop(SOUND_TYPE id);
};

#endif
