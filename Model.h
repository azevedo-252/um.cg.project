/**
 * Classe abstracta para um modelo desenhavel em OpenGL
 */

#ifndef _model_h
#define _model_h

#include "Vertex.h"
#include "Config.h"

extern Config conf;

class Model {

public:
	// posicao do modelo no mundo
	Vertex *coords;
	// direccao, no eixo XOZ, para onde ele deve estar virado
	Vertex *direction;
	float ang_x, ang_y;
	// equivalente ao up-vector da camara
	Vertex rotation;
	
	// construtores nao precisam de nada
	Model() { }

	virtual void render() { }

	/** distancia deste modelo a um ponto */
	float distance(Vertex* coords);

//	/** vector da direccao deste modelo a um ponto */
//	Vertex* directionVector(Vertex* coords);
//
//	/** angulo da direccao deste modelo a um ponto */
//	float directionAngle(Vertex* coords);
};

#endif
