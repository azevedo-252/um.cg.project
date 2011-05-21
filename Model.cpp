/**
 * Model.cpp
 */

#include "Model.h"

#include <math.h>

/** distancia deste modelo a um ponto */
float Model::distance(Vertex* coords) {
	return this->coords->distance(coords);
}

///** vector da direccao deste modelo a um ponto */
//Vertex* Model::directionVector(Vertex* coords) {
//	return new Vertex(coords->x - this->coords->x, 0, coords->z - this->coords->z);
//}
//
//float Model::directionAngle(Vertex* coords) {
//	Vertex* dir = directionVector(coords);
//	float distance = this->distance(coords);
//
//	return acos(dir->x / distance);
//}
