/*
 *
 * File:   Key.cpp
 * Author: gabriel
 * 
 * Created on 9 de Abril de 2011, 17:42
 */

#include "Key.h"
#include "externs.h"

#include <math.h>

using namespace std;

Key::Key(const string &path) : Model_MD2(path) {
    coords = new Vertex(0, 0, 0);
    md2_rendermode = 0;

    catched = false;
}


void Key::set_pos(Vertex* new_coords) {
    coords->x = new_coords->x;
    coords->y = new_coords->y;
    coords->z = new_coords->z;
}

void Key::render() {
	if (!catched) {
		glPushMatrix();
		glTranslatef(coords->x, coords->y, coords->z);
		glRotatef(glutGet(GLUT_ELAPSED_TIME) * 0.1, 0, 1, 0);
		md2_model->drawPlayerItp(true, static_cast<Md2Object::Md2RenderMode> (md2_rendermode));
		glPopMatrix();
	}
}

void Key::update() {
	if (!catched) {
		direction = this->coords->directionVector(g_player->coords);
		dir_dist = (sqrt(pow(direction->x, 2) + pow(direction->z, 2)));

		if (dir_dist < g_keys->catch_dist) {
			catched = true;
			g_keys->keys_left--;
			Sound::play(SOUND_KEY_CATCH);
		}
	}
}
