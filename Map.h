/**
 * Classe que gere o mapa de jogo
 */

#ifndef _map_h
#define _map_h

#include "Textures.h"

#include <GL/glut.h>
#include <IL/ilut.h>

#include "Model.h"

class Map : public Model {

private:
	TexData tex_soil;

public:
	int width;
	int grid_n;
	float grid_width;
	float wall_dist;

	//construtores
	Map();
	~Map();

	void render();

	/** move o vector para as coordenadas mais proximas dentro da area jogavel */
	void adjustPlayableCoords(Vertex* coords);

	/** determinal se as coordenadas estao dentro da area jogavel */
	bool isPlayableCoords(Vertex* coords);
};

#endif
