/*
 * Textures.cpp
 */

#include "Textures.h"

#include <GL/glut.h>
#include <IL/il.h>

TexData Textures::textures[TEXTURE_COUNT];

void Textures::load() {
    Textures::loadSingle(TERRAIN, (char *) "resources/textures/soil.jpg");
    Textures::loadSingle(SKYBOX1, (char *) "resources/textures/sky/face1.pcx");
    Textures::loadSingle(SKYBOX2, (char *) "resources/textures/sky/face2.pcx");
    Textures::loadSingle(SKYBOX3, (char *) "resources/textures/sky/face3.pcx");
    Textures::loadSingle(SKYBOX4, (char *) "resources/textures/sky/facetop.jpg");
    Textures::loadSingle(SKYBOX5, (char *) "resources/textures/sky/face5.pcx");
    Textures::loadSingle(SKYBOX6, (char *) "resources/textures/sky/face62.jpg");
}

void Textures::loadSingle(enum texture_id id, char* path) {
    /** textura do terreno */
    ilGenImages(1, &(textures[id].id));
    ilBindImage(textures[id].id);
    ilLoadImage(path);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    textures[id].w = ilGetInteger(IL_IMAGE_WIDTH);
    textures[id].h = ilGetInteger(IL_IMAGE_HEIGHT);
    textures[id].data = ilGetData();

    glGenTextures(1, &(textures[id].gl_id)); // unsigned int texID - variavel global;
    glBindTexture(GL_TEXTURE_2D, textures[id].gl_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, textures[id].w, textures[id].h,
    			 GL_RGBA, GL_UNSIGNED_BYTE, textures[id].data);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[id].w, textures[id].h,
    //        0, GL_RGBA, GL_UNSIGNED_BYTE, textures[id].data);
    glBindTexture(GL_TEXTURE_2D, 0);

}

TexData Textures::get(enum texture_id id) {
    return textures[id];
}
