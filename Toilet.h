/**
 * Define uma class que reperesenta uma Sanita
 */
#ifndef _toilet_h
#define _toilet_h

#include "Model_MD2.h"
#include "Vertex.h"
#include "Config.h"
#include <math.h>

class Toilet : Model_MD2 {
private:

public:
	float dir_dist;
    Vertex *coords;
    Toilet(const std::string &path);
    void render();
};

#endif
