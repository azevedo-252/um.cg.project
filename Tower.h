#ifndef _TOWER_H
#define _TOWER_H

#include "Model_MD2.h"
#include "Vertex.h"
#include "Config.h"
#include "Player.h"
#include <math.h>

extern Player *g_player;

class Tower : public Model_MD2 {
private:
	int id;
	static GLfloat _scale;
	static float _max_dist;
	Vertex *direction;
	bool can_fire;

	void init_render();
public:
	static float bullet_delay;
	float dir_dist;

	Tower(int id, const std::string &path);
	void set_pos(Vertex *new_coords);
	void render();
	void update();
	void fire();
	bool canFire();
	void allowFire();
	void disallowFire();
};

#endif
