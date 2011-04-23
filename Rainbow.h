/**
 * Define uma class que reperesenta um arco iris.
 */
 
#ifndef _Rainbow_h
#define _Rainbow_h

#include "Model.h"
#include "Vertex.h"

#include "InputManager.h"

class Rainbow : Model {

public:
	float ang_x, ang_y;
	float dir_dist;
	float win_distance;
	bool win;

	Rainbow();

	void render();
    void update();
};

#endif
