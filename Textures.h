/*
 * Textures.h
 */

#ifndef _TEXTURES_H
#define _TEXTURES_H

enum texture_id {
	TERRAIN,
	SKYBOX1,
	SKYBOX2,
        SKYBOX3,
        SKYBOX4,
        SKYBOX5,
        SKYBOX6,
	TEXTURE_COUNT,
};

typedef struct texture_data {
	unsigned int id;
	unsigned int gl_id;
	int w, h;
	unsigned char *data;
} TexData;

class Textures {

public:
	static TexData textures[TEXTURE_COUNT];

	/** carrega as texturas */
	static void load();

	/** carrega uma textura para memoria */
	static void loadSingle(enum texture_id id, char* path);

	/** Devolve info sobre uma textura */
	static TexData get(enum texture_id id);
};

#endif
