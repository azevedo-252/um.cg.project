/* 
 * File:   Lighting.cpp
 * Author: naps62
 * 
 * Created on May 18, 2011, 1:37 AM
 */

#include "Lighting.h"

#include "externs.h"

Lighting::Lighting() {
	pos[0] = g_player->coords->x;
	pos[1] = g_player->coords->y + 10;
	pos[2] = g_player->coords->z;
	pos[3] = 0.0;
	
	amb[0] = 1.0;
	amb[1] = 0.8;
	amb[2] = 0.8;
	
	diff[0] = 0.0;
	diff[1] = 0.0;
	diff[2] = 0.0;
}


Lighting::~Lighting() {
}

void Lighting::render() {
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}

