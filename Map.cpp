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
	tex_height = Textures::get(TERRAIN_HEIGHT);

	width = conf.rint("map:width");
	grid_n = conf.rint("map:grid_n");
	max_height = conf.rint("map:max_height");
	grid_width = width / grid_n;
	height_map_ratio = width / tex_height.w;

	wall_dist = conf.rint("map:wall_distance");
}

Map::~Map() {
}

void Map::render() {
	int x = 0, y = 0;

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex_soil.gl_id);

	for(x = 0; x < grid_n; x++) {
		glBegin(GL_TRIANGLE_STRIP);
			for(y = 0; y <= grid_n; y++) {
				glTexCoord2f(y, 0); this->heightedVertex(grid_width, x+1, y); //glVertex3f(grid_width * (x+1), 0.0, grid_width * y);
				glTexCoord2f(y, 1); this->heightedVertex(grid_width, x, y); //glVertex3f(grid_width * x,     0.0, grid_width * y);
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

float Map::map_h(int x, int z) {
	return (int) (this->tex_height.data[x + this->tex_height.w * z] * this->max_height) / 10;
}

float Map::triangulateHeight(float x, float z) {
	double intX, intZ;
	float fracX, fracZ;

	x /= grid_width;
	z /= grid_width;
	
	fracX = modf(x, &intX);
	fracZ = modf(z, &intZ);

	float alt1, alt2;

	alt1 = this->map_h(intX,     intZ) * (1 - fracZ) + this->map_h(intX,     intZ + 1) * fracZ;
	alt2 = this->map_h(intX + 1, intZ) * (1 - fracZ) + this->map_h(intX + 1, intZ + 1) * fracZ;

	return alt1 * (1 - fracX) + alt2 * fracX;
}

void Map::heightedVertex(float mul, int x, int z) {
	glVertex3f(mul * x, this->map_h(x, z), mul * z);
}