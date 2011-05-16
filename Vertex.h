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
	Vertex operator+(Vertex &v);
	Vertex operator-(Vertex &v);
	Vertex operator*(Vertex &v);
        
	Vertex operator*(float num);
	Vertex operator+(float num);
        Vertex operator-(float num);
        
//	Vertex operator-(void);
        
	Vertex & operator+=(Vertex &v);
	Vertex & operator-=(Vertex &v);
        
        void mult(float num);
        void sum(float num);
        void sub(float num);
        
	float distance(Vertex* v2);
	float inner_product(Vertex *v);
	void normalize();
	/** debug */
	void dump();
};

#endif
