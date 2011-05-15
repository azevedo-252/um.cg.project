/* 
 * File:   Towers.h
 * Author: gabriel
 *
 * Created on 14 de Abril de 2011, 17:53
 */

#ifndef TOWERS_H
#define	TOWERS_H

#include "Tower.h"
#include "Player.h"

extern Player* g_player;
extern Config conf;


class Towers : Model_MD2 {
public:
	GLuint tower_list;
	
    int num_towers;
    Tower **towers;
    Towers(const string &path);
	void createTowerList();
    int get_closest_distance();
    void render();
    void update();
private:

};

#endif	/* TOWERS_H */

