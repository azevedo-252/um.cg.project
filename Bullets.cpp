/**
 * Bullets.cpp
 */

#include <math.h>

#include "externs.h"
#include "Bullets.h"
#include "Map.h"

int Bullets::anim_start;
int Bullets::anim_end;

Bullets::Bullets(const string &path) : Model_MD2(path) {
	anim_start = conf.rint("game:bullet_walk_frame");
	anim_end = conf.rint("game:bullet_walk_frame_end");
	md2_rendermode = 0;
}

void Bullets::update() {
	for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end();) {
		it->update();
		if (! g_map->isPlayableCoords(it->coords)) {
			it = bullets.erase(it);
		}
		else it++;
	}
}

void Bullets::updateFrames() {
	for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++) {
		it->inc_frame();
	}
}

void Bullets::render() {
	int frame;
	Vertex *coords;
	float ang;
	
	for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++) {
		frame = it->anim->current_frame;
		coords = it->coords;
		ang = it->ang;

		glPushMatrix();
		glTranslatef(coords->x, coords->y, coords->z);
		glRotatef(ang, 0, 1, 0);
		md2_model->drawPlayerFrame(frame, static_cast<Md2Object::Md2RenderMode> (md2_rendermode));
		glPopMatrix();
	}
}

void Bullets::addBullet(Vertex* coords, float ang, float ang_rad) {
	Bullet *b = new Bullet(coords, ang, ang_rad);
	bullets.push_front(*b);
}