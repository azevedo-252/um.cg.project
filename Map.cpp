#include <iostream>
using namespace std;

#include "Map.h"

#include "Textures.h"
#include "GLManager.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include "stb_image.c"

Map::Map() {
	tex_soil = Textures::get(TERRAIN);

	width = GLManager::distance(conf.rint("map:width"));
	grid_n = GLManager::distance(conf.rint("map:grid_n"));
	grid_width = width / (float) grid_n;

	wall_dist = conf.rfloat("map:wall_distance");
}

Map::~Map() {
}

void Map::render() {
	int x = 0, y = 0;

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex_soil.gl_id);

	for(x = 0; x < grid_n; x++) {
		glBegin(GL_QUAD_STRIP);
			for(y = 0; y < grid_n; y++) {
				glTexCoord2f(y, 0); glVertex3f(grid_width * (x+1), 0.0, grid_width * y);
				glTexCoord2f(y, 1); glVertex3f(grid_width * x,     0.0, grid_width * y);
				}
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void Map::adjustPlayableCoords(Vertex* coords) {
    if (coords->x < wall_dist)
        coords->x = wall_dist;
    else if (coords->x >= width - wall_dist)
        coords->x = width - wall_dist;

    if (coords->z < wall_dist)
        coords->z = wall_dist;
    else if (coords->z >= width - wall_dist)
        coords->z = width - wall_dist;
}

bool Map::isPlayableCoords(Vertex* coords) {
	return (coords->x >= wall_dist &&
			coords->x < width - wall_dist &&
			coords->z >= wall_dist &&
			coords->z < width - wall_dist);
}
