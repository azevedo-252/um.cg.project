/**
 * Define um vertice 3D
 */

#ifndef _vertex_h
#define _vertex_h

#define VX 0
#define VY 1
#define VZ 2

class Vertex {

public:
	float x, y, z;

	/** constructors */
	Vertex();
	Vertex(float x, float y, float z);
	~Vertex();

	/** operators */
	const Vertex operator+(const Vertex &v);
	const Vertex operator-(const Vertex &v);
	Vertex & operator+=(const Vertex &v);
	Vertex & operator-=(const Vertex &v);
	float distance(Vertex* v2);

	/** debug */
	void dump();
};

#endif
