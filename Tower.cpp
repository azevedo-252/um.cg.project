
#include "Tower.h"
#include "Bullet.h"
#include "Bullets.h"
#include "externs.h"
#include "GLManager.h"
#include <iostream>

using namespace std;

GLfloat Tower::_scale = 7.5;
float Tower::_max_dist;
float Tower::bullet_delay;

Tower::Tower(int id, const string &path) : Model_MD2(path) {
	this->id = id;
    coords = new Vertex(0, 0, 0);
    md2_rendermode = 0;
    set_scale(conf.rfloat("game:tower_scale"));
    _max_dist = conf.rfloat("game:tower_range");
	can_fire = true;
	dir_dist = 999999;
}

void Tower::set_pos(Vertex *new_coords) {
    coords->x = new_coords->x;
    coords->y = new_coords->y;
    coords->z = new_coords->z;
}

void Tower::init_render() {
    direction = new Vertex(g_player->coords->x - coords->x, 0, g_player->coords->z - coords->z);
    dir_dist = (sqrt(pow(direction->x, 2) + pow(direction->z, 2)));

    direction = this->directionVector(g_player->coords);
    dir_dist = this->distance(g_player->coords);
}

void Tower::update() {
	//init_render();
	direction = this->directionVector(g_player->coords);
    dir_dist = (sqrt(pow(direction->x, 2) + pow(direction->z, 2)));

	if (dir_dist < _max_dist) {
		ang_x = acos(direction->x / dir_dist);
		if (g_player->coords->z > coords->z)
			ang_x = -ang_x;
		
		fire();
	}
}

void Tower::render() {
    glPushMatrix();
    glTranslatef(coords->x, coords->y, coords->z);
    glRotatef(90 + (ang_x * 180) / M_PI, 0, 1, 0);
    md2_model->drawPlayerItp(true, static_cast<Md2Object::Md2RenderMode> (0));
    glPopMatrix();
}

void Tower::fire() {
	if (canFire()) {
		disallowFire();
		g_bullets->addBullet(coords, 90 + (ang_x * 180) / M_PI, -ang_x);
		glutTimerFunc(Tower::bullet_delay, GLManager::allowTowerFire, this->id);
	}
}

bool Tower::canFire() {
	return can_fire;
}

void Tower::allowFire() {
	can_fire = true;
}

void Tower::disallowFire() {
	can_fire = false;
}