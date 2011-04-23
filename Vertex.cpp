#include <iostream>
#include <assert.h>

using namespace std;

#include "Vertex.h"

#include <math.h>

Vertex::Vertex() {
	x = 0; y = 0; z = 0;
}

Vertex::Vertex(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
}

Vertex::~Vertex() {
	return;
}

const Vertex Vertex::operator+(const Vertex &v) {
	Vertex res(x + v.x, y + v.y, z + v.z);
	return res;
}

const Vertex Vertex::operator-(const Vertex &v) {
	Vertex res(x - v.x, y - v.y, z - v.z);
	return res;
}

Vertex & Vertex::operator+=(const Vertex &v) {
	x += v.x; y += v.y; z += v.z;
	return *this;
}

Vertex & Vertex::operator-=(const Vertex &v) {
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

void Vertex::dump() {
	cout.precision(2);
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

float Vertex::distance(Vertex* v2) {
	return sqrt(pow(this->x - v2->x, 2) + pow(this->y - v2->y, 2) + pow(this->z - v2->x, 2));
}
