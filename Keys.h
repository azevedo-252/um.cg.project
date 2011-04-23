/* 
 * File:   Towers.h
 * Author: gabriel
 *
 * Created on 14 de Abril de 2011, 17:53
 */

#ifndef _KEYS_H
#define	_KEYS_H

#include "Key.h"
#include "Player.h"

class Keys {
public:
    int num_keys, keys_left;
    float catch_dist;

    Key **keys;
    Keys();
    void render();
    void update();

    int get_closest_distance();
private:

};

#endif	/* _KEYS_H */

