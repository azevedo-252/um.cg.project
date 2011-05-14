/**
 * Define uma class que reperesenta um player model.
 */
#ifndef _BULLET_H
#define _BULLET_H

#include "Vertex.h"
#include "Frame.h"


#include "InputManager.h"

class Bullet {
public:
    Frame *anim;
	Vertex *coords;
    float ang, ang_rad; //ang em graus
    static float speed;

    Bullet(Vertex *coords, float ang, float ang_rad);
	~Bullet();

    void update();
    void render();
    
    void inc_frame();
};

#endif
