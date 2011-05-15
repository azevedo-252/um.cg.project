/*
 * Textures.cpp
 */

#include "Textures.h"

#include <IL/il.h>

TexData Textures::textures[TEXTURE_COUNT];

void Textures::load() {
    Textures::loadSingle(TERRAIN, "resources/textures/map_texture.jpg",GL_LINEAR_MIPMAP_LINEAR);
	
	Textures::loadHeightMap("resources/textures/map_height.jpg");
	
    Textures::loadSingle(SKYBOX1, "resources/textures/sky/face1.pcx",	GL_LINEAR);
    Textures::loadSingle(SKYBOX2, "resources/textures/sky/face2.pcx",	GL_LINEAR);
    Textures::loadSingle(SKYBOX3, "resources/textures/sky/face3.pcx",	GL_LINEAR);
    Textures::loadSingle(SKYBOX4, "resources/textures/sky/facetop.jpg",	GL_LINEAR);
    Textures::loadSingle(SKYBOX5, "resources/textures/sky/face5.pcx",	GL_LINEAR);
    Textures::loadSingle(SKYBOX6, "resources/textures/sky/face62.jpg",	GL_LINEAR);
}

void Textures::loadSingle(enum texture_id id, string path, GLuint gl_filter) {
    /** textura do terreno */
    ilGenImages(1, &(textures[id].id));
    ilBindImage(textures[id].id);
    ilLoadImage(path.c_str());
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    textures[id].w = ilGetInteger(IL_IMAGE_WIDTH);
    textures[id].h = ilGetInteger(IL_IMAGE_HEIGHT);
    textures[id].data = ilGetData();

    glGenTextures(1, &(textures[id].gl_id)); // unsigned int texID - variavel global;
    glBindTexture(GL_TEXTURE_2D, textures[id].gl_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter );

    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, textures[id].w, textures[id].h,
    			 GL_RGBA, GL_UNSIGNED_BYTE, textures[id].data);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[id].w, textures[id].h,
    //        0, GL_RGBA, GL_UNSIGNED_BYTE, textures[id].data);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Textures::loadHeightMap(string path) {
	ilGenImages(1, &(textures[TERRAIN_HEIGHT].id));

	ilBindImage(textures[TERRAIN_HEIGHT].id);
	ilLoadImage(path.c_str());
	ilConvertImage(IL_LUMINANCE,IL_UNSIGNED_BYTE);
	
	textures[TERRAIN_HEIGHT].w = ilGetInteger(IL_IMAGE_WIDTH);
	textures[TERRAIN_HEIGHT].h = ilGetInteger(IL_IMAGE_HEIGHT);
	textures[TERRAIN_HEIGHT].data = ilGetData();
}

TexData Textures::get(enum texture_id id) {
    return textures[id];
}