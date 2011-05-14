#include "Player.h"
#include "InputManager.h"
#include "GLManager.h"
#include "Config.h"

#include "externs.h"
#include "Frame.h"
#include "Bullet.h"

#include <math.h>

extern Config conf;

using namespace std;

float Bullet::speed;

Bullet::Bullet(Vertex *coords, float ang, float ang_rad) {
	this->coords = new Vertex();
	this->coords->x = coords->x;
	this->coords->z = coords->z;
	this->coords->y = g_map->triangulateHeight(coords->x, coords->z);
	
	cout << "ang: " << ang << endl;
	this->ang = ang;
	this->ang_rad = ang_rad;
	
	this->anim = new Frame();
	this->anim->add_anim(MOVE_WALK, Bullets::anim_start, Bullets::anim_end);
	this->anim->set_anim(MOVE_WALK);
}

Bullet::~Bullet() {
	
}

void Bullet::update() {
	coords->x += cos(ang_rad) * speed;
	coords->z += sin(ang_rad) * speed;
	coords->y = g_map->triangulateHeight(coords->x, coords->z);
}

void Bullet::inc_frame() {
	this->anim->inc_frame();
}
