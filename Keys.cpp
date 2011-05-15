/* 
 * File:   keys.cpp
 * Author: gabriel
 * 
 * Created on 14 de Abril de 2011, 17:53
 */

#include "Keys.h"
#include "GLManager.h"

#include "externs.h"

Keys::Keys() {
    catch_dist = conf.rfloat("game:key_catch_distance");

	num_keys = conf.rint("game:num_keys");
    keys_left = num_keys;
	float keys_min_distance = conf.rfloat("game:keys_min_distance");

	keys = (Key **) calloc(num_keys, sizeof (Key *));

	for (int i = 0; i < num_keys; i++) {
	    keys[i] = new Key(conf.rstring("models:key"));
	    Vertex* pos = NULL;
	    do {
	     	pos = GLManager::randomVertex();
        	g_map->adjustPlayableCoords(pos);

	       	for(int j = 0; j < i && pos != NULL; j++) {
	       		if (pos->distance(keys[i]->coords) < keys_min_distance)
	       			pos = NULL;
	       	}
        	// as chaves nao podem estar muito proximas das torres
        	for(int j = 0; j < g_towers->num_towers && pos != NULL; j++) {
        		if (pos->distance(g_towers->towers[j]->coords) < keys_min_distance)
        			pos = NULL;
        		}
        	// as chaves tem que ficar na area jogavel do terreno
        } while(pos == NULL);

		pos->y = g_map->triangulateHeight(pos->x, pos->z);
	    keys[i]->set_pos(pos);
    }

}

void Keys::render() {
    for (int i = 0; i < num_keys; i++) {
        keys[i]->render();
    }
}

void Keys::update() {
	for (int i = 0; i < num_keys; i++) {
		keys[i]->update();
	}
}

int Keys::get_closest_distance() {
    int distance = 9999999;
    for (int i = 0; i < num_keys; i++) {
        if (keys[i]->catched == false && keys[i]->dir_dist < distance) {
            distance = keys[i]->dir_dist;
        }
    }
    return distance;
}
