/* 
 * File:   Radar.h
 * Author: gabriel
 *
 * Created on 9 de Abril de 2011, 18:00
 */

#ifndef RADAR_H
#define	RADAR_H

#include "Vertex.h"
#include "Player.h"
#include "Towers.h"




class Radar {

public:
    float dist;
    float range;
    Radar();
    void set_pos(Vertex *new_coords);
    void update();
    void render();
private:
    void setOrthographicProjection();
    void resetPerspectiveProjection();
    Vertex *screen_coords;
};

#endif	/* RADAR_H */

