/* 
 * File:   Bullets.h
 * Author: naps62
 *
 * Created on April 26, 2011, 12:27 PM
 */

#ifndef BULLETS_H
#define	BULLETS_H

#include <list>

using namespace std;

#include "Model_MD2.h"
#include "Bullet.h"


#define BULLET_HIT_DIST 2

class Bullets {
private:
	list<Bullet> bullets;
	GLuint *bulletFrames;	
        void end_game();
public:
	static int anim_start, anim_end;
	
	Bullets(const string &path);
	
	void createBulletsLists(const string &path);
	
	void update();
	void updateFrames();
	void render();
	void addBullet(Vertex *coords, float ang, float ang_rad);
};

#endif	/* BULLETS_H */

