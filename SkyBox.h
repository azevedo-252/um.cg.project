/* 
 * File:   SkyBox.h
 * Author: gabriel
 *
 * Created on 16 de Abril de 2011, 22:53
 */

#ifndef SKYBOX_H
#define	SKYBOX_H

#include "Textures.h"

class SkyBox {
public:
    SkyBox();
    void render();
private:
    TexData face1;
    TexData face2;
    TexData face3;
    TexData face4;
    TexData face5;
    TexData face6;
	
	GLfloat mat_amb[4];
	GLfloat mat_diff[4];
	GLfloat mat_spec[4];
};

#endif	/* SKYBOX_H */

