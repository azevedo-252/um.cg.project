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
	pos[3] = conf.rfloat("light:pos_w");
	
	amb[0] = conf.rfloat("light:amb_r");
	amb[1] = conf.rfloat("light:amb_g");
	amb[2] = conf.rfloat("light:amb_b");
	
	diff[0] = conf.rfloat("light:dif_r");
	diff[1] = conf.rfloat("light:dif_g");
	diff[2] = conf.rfloat("light:dif_b");
}


Lighting::~Lighting() {
}

void Lighting::render() {
	pos[0] = g_player->coords->x;
	pos[1] = g_player->coords->y + 10;
	pos[2] = g_player->coords->z;
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}

