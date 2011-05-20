#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>

#include "Map.h"
#include "Textures.h"
#include "GLManager.h"

#include "stb_image.c"

Map::Map() {
	tex_soil = Textures::get(TERRAIN);
	tex_height = Textures::get(TERRAIN_HEIGHT);

	width = conf.rint("map:width");
	grid_n = conf.rint("map:grid_n");
	max_height = conf.rint("map:max_height");
	grid_width = width / grid_n;
	height_map_ratio = tex_height.w / grid_n;
	cout << height_map_ratio << endl;

	wall_dist = conf.rint("map:wall_distance");

#ifndef goku
	initVBO();
#endif
}

Map::~Map() {
	for (int x = 0; x < n_strips; x++) {
		free(grid_strips[x]);
	}
	free(grid_strips);
}

Vertex* Map::vertexFromBuffer(float *buff, int x, int y) {
	int first = (x * grid_n + y) * 3;
	return new Vertex(buff[first], buff[first + 1], buff[first + 2]);
}

void Map::initVBO() {
	float *vertexB, *texB, *normalB;
	int vertexSize = grid_n * grid_n * 3 * sizeof (float);
	int texSize = grid_n * grid_n * 2 * sizeof (float);
	int normalSize = grid_n * grid_n * 3 * sizeof (float);
	int stripSize = grid_n * 2 * sizeof (unsigned int);
	n_strips = grid_n - 1;

	//cria espaco temporario para preencher os buffers
	vertexB = (float *) malloc(vertexSize);
	texB = (float *) malloc(texSize);
	normalB = (float *) malloc(normalSize);
	grid_strips = (unsigned int **) malloc(sizeof (unsigned int *) * n_strips);

	//preencher o buffer de vertices
	float *vertexAux = vertexB;
	float *texAux = texB;
	for (int x = 0; x < grid_n; x++) {
		for (int y = 0; y < grid_n; y++) {
			vertexAux[0] = grid_width * x;
			vertexAux[2] = grid_width * y;
			vertexAux[1] = this->map_h(x, y);
			vertexAux += 3;

			texAux[0] = x;
			texAux[1] = y;
			texAux += 2;
		}
	}
	
	cout << tex_height.h << endl;

	float *normalAux = normalB;
	for (int x = 0; x < grid_n; x++) {
		for (int y = 0; y < grid_n; y++) {
			Vertex *N = (x == 0) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x - 1, y);
			Vertex *S = (x == grid_n - 1) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x + 1, y);
			Vertex *W = (y == 0) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x, y - 1);
			Vertex *E = (y == grid_n - 1) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x, y + 1);

			Vertex *normA = new Vertex(S->x - N->x, S->y - N->y, S->z - N->z);
			Vertex *normB = new Vertex(E->x - W->x, E->y - W->y, E->z - W->z);

			normalAux[0] = normA->y * normB->z - normA->z * normB->y;
			normalAux[1] = normA->z * normB->x - normA->x * normB->z;
			normalAux[2] = normA->x * normB->y - normA->y * normB->y;
			normalAux += 3;
		}
	}

	//preenche as strips
	for (int x = 0; x < n_strips; x++) {
		grid_strips[x] = (unsigned int *) malloc(stripSize);
		unsigned int *stripAux = grid_strips[x];
		for (int y = 0; y < grid_n; y++) {
			stripAux[0] = y + (x + 1) * grid_n;
			stripAux[1] = y + x * grid_n;
			stripAux += 2;
		}
	}

	// debug
	//	vertexAux = vertexB;
	//	texAux    = texB;
	//	for(int x = 0; x < grid_n * grid_n; x++) {
	//		cout << vertexAux[0] << " " << vertexAux[1] << " " <<vertexAux[2] << " - " << texAux[0] << " " << texAux[1] << endl;
	//		vertexAux+=3; texAux+=2;
	//	}


	//gera e envia os buffers
	glGenBuffers(MAP_BUFF_COUNT, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[MAP_VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexB, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[MAP_TEX]);
	glBufferData(GL_ARRAY_BUFFER, texSize, texB, GL_STATIC_DRAW);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[MAP_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, normalSize, normalB, GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, 0);

	//liberta os buffers temporarios
	free(vertexB);
	free(texB);
	free(normalB);
}

void Map::render() {
	int x = 0, y = 0;

	glBindTexture(GL_TEXTURE_2D, tex_soil.gl_id);
	
#ifndef goku

	//GLfloat mat_amb_diff[] = { 0.5, 0.5, 0.5, 1.0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);

	for (int x = 0; x < n_strips; x++) {
		glDrawElements(GL_TRIANGLE_STRIP, grid_n * 2, GL_UNSIGNED_INT, grid_strips[x]);

	}

	GLManager::resetMaterials();

#else
		for(x = 0; x < grid_n; x++) {
			glBegin(GL_TRIANGLE_STRIP);
				for(y = 0; y <= grid_n; y++) {
					glTexCoord2f(y, 0); this->heightedVertex(grid_width, x+1, y); //glVertex3f(grid_width * (x+1), 0.0, grid_width * y);
					glTexCoord2f(y, 1); this->heightedVertex(grid_width, x, y); //glVertex3f(grid_width * x,     0.0, grid_width * y);
					}
			glEnd();
		}
#endif
	glBindTexture(GL_TEXTURE_2D, 0);
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
#ifndef rocket
	int heightVal = this->tex_height.data[(int) (x + this->tex_height.w * z)];
	return (float) heightVal * max_height / 256;
#else
	return 0;
#endif
}

float Map::triangulateHeight(float x, float z) {
	double intX, intZ;
	float fracX, fracZ;

	x /= grid_width;
	z /= grid_width;

	fracX = modf(x, &intX);
	fracZ = modf(z, &intZ);

	float alt1, alt2;

	alt1 = this->map_h(intX, intZ) * (1 - fracZ) + this->map_h(intX, intZ + 1) * fracZ;
	alt2 = this->map_h(intX + 1, intZ) * (1 - fracZ) + this->map_h(intX + 1, intZ + 1) * fracZ;

	return alt1 * (1 - fracX) + alt2 * fracX;
}

void Map::heightedVertex(float mul, int x, int z) {
	glVertex3f(mul * x, this->map_h(x, z), mul * z);
}