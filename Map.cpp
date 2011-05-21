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

	loadHeightMap();
	wall_dist = conf.rint("map:wall_distance");

	drawNormals = conf.rint("debug:draw_normals") == 1;
	normalDist = conf.rint("debug:normal_dist");

	mat_amb[0] = conf.rfloat("map:amb_r");
	mat_amb[1] = conf.rfloat("map:amb_g");
	mat_amb[2] = conf.rfloat("map:amb_b");
	mat_amb[3] = conf.rfloat("map:amb_w");
	
	mat_diff[0] = conf.rfloat("map:diff_r");
	mat_diff[1] = conf.rfloat("map:diff_g");
	mat_diff[2] = conf.rfloat("map:diff_b");
	mat_diff[3] = conf.rfloat("map:diff_w");
	
	mat_spec[0] = conf.rfloat("map:spec_r");
	mat_spec[1] = conf.rfloat("map:spec_g");
	mat_spec[2] = conf.rfloat("map:spec_b");
	mat_spec[3] = conf.rfloat("map:spec_w");

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

void Map::loadHeightMap() {
	int heightMapSize = tex_height.w * tex_height.h;
	heightMapData = (float *) malloc(sizeof (float) * heightMapSize);
	for (int i = 0; i < heightMapSize; i++) {
		heightMapData[i] = (float) tex_height.data[i] * max_height / (float) 256;
	}
}

Vertex* Map::vertexFromBuffer(float *buff, int x, int y) {
	int first = (x * grid_n + y) * 3;
	return new Vertex(buff[first], buff[first + 1], buff[first + 2]);
}

void Map::initVBO() {
	//float *vertexB, *texB, *normalB;
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

	float *normalAux = normalB;
	for (int x = 0; x < grid_n; x++) {
		for (int y = 0; y < grid_n; y++) {
			Vertex *N = (x == 0) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x - 1, y);
			Vertex *S = (x == grid_n - 1) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x + 1, y);
			Vertex *W = (y == 0) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x, y - 1);
			Vertex *E = (y == grid_n - 1) ? vertexFromBuffer(vertexB, x, y) : vertexFromBuffer(vertexB, x, y + 1);

			Vertex *normA = new Vertex(S->x - N->x, S->y - N->y, S->z - N->z);
			Vertex *normB = new Vertex(E->x - W->x, E->y - W->y, E->z - W->z);

			Vertex *norm = new Vertex(normA->y * normB->z - normA->z * normB->y,
				normA->z * normB->x - normA->x * normB->z,
				normA->x * normB->y - normA->y * normB->y);

			norm->normalize();

			normalAux[0] = -norm->x;
			normalAux[1] = -norm->y;
			normalAux[2] = -norm->z;
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
	free(texB);
	if (drawNormals == false) {
		free(vertexB);
		free(normalB);
	}
}

void Map::render() {
	int x = 0, y = 0;

	glBindTexture(GL_TEXTURE_2D, tex_soil.gl_id);

#ifndef goku

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);

	for (int x = 0; x < n_strips; x++) {
		glDrawElements(GL_TRIANGLE_STRIP, grid_n * 2, GL_UNSIGNED_INT, grid_strips[x]);

	}

	if (drawNormals) {
		float *vertexAux = vertexB;
		float *normalAux = normalB;
		for (int x = 0; x < grid_n; x++) {
			for (int y = 0; y < grid_n; y++) {

				glBegin(GL_LINES);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(vertexAux[0], vertexAux[1], vertexAux[2]);
				glVertex3f(vertexAux[0] + normalAux[0] * normalDist, vertexAux[1] + normalAux[1] * normalDist, vertexAux[2] + normalAux[2] * normalDist);
				glEnd();
				vertexAux += 3;
				normalAux += 3;
			}
		}
	}

	GLManager::resetMaterials();

#else
	for (x = 0; x < grid_n; x++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (y = 0; y <= grid_n; y++) {
			glTexCoord2f(y, 0);
			this->heightedVertex(grid_width, x + 1, y); //glVertex3f(grid_width * (x+1), 0.0, grid_width * y);
			glTexCoord2f(y, 1);
			this->heightedVertex(grid_width, x, y); //glVertex3f(grid_width * x,     0.0, grid_width * y);
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
	return this->heightMapData[x + this->tex_height.w * z];
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
