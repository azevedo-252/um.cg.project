/**
 * Classe que gere o mapa de jogo
 */

#ifndef _map_h
#define _map_h

#include "Textures.h"

#include <GL/glut.h>
#include <IL/ilut.h>

#include "Model.h"

typedef enum enum_map_buffs {
	MAP_VERTEX,
	MAP_NORMAL,
	MAP_TEX,

	MAP_BUFF_COUNT
} MAP_BUFFS;

class Map : public Model {
private:
	TexData tex_soil;
	TexData tex_height;

	GLuint buffers[MAP_BUFF_COUNT];
	unsigned int **grid_strips;
	int n_strips;

public:
	int width;
	float grid_n;
	float max_height;
	float height_map_ratio;
	float grid_width;
	float wall_dist;

	//construtores
	Map();
	~Map();

	Vertex* vertexFromBuffer(float *buff, int x, int y);
	void initVBO();
	
	void render();

	/** move o vector para as coordenadas mais proximas dentro da area jogavel */
	void adjustPlayableCoords(Vertex* coords);

	/** determinal se as coordenadas estao dentro da area jogavel */
	bool isPlayableCoords(Vertex* coords);

	float map_h(int x, int z);
	float triangulateHeight(float x, float z);

	void heightedVertex(float mul, int x, int z);
};

#endif
