#ifndef _TOWER_H
#define _TOWER_H

#include "Vertex.h"
#include "Config.h"
#include "Player.h"
#include <math.h>

extern Player *g_player;

class Tower : public Model {
private:
    GLdouble radius;
    int id;
    static GLfloat _scale;
    static float _max_dist;
    Vertex *direction;
    bool can_fire;
	
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
