#include <iostream>
#include <assert.h>

using namespace std;

#include "Vertex.h"

#include <math.h>

Vertex::Vertex() {
    x = 0;
    y = 0;
    z = 0;
}

Vertex::Vertex(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vertex::~Vertex() {
    return;
}

//Vertex Vertex::operator-(void) {
//
//	Vertex res;
//
//	res.x = -x;
//	res.y = -y;
//	res.z = -z;
//
//	return(res);
//}

Vertex Vertex::operator+(Vertex &v) {
    Vertex res(x + v.x, y + v.y, z + v.z);
    return res;
}

Vertex Vertex::operator-(Vertex &v) {
    Vertex res(x - v.x, y - v.y, z - v.z);
    return res; 
}

Vertex & Vertex::operator+=(Vertex &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vertex & Vertex::operator-=(Vertex &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vertex Vertex::operator*(Vertex &v) {
    Vertex res;

    res.x = this->y * v.z - this->z * v.y;
    res.y = this->z * v.x - this->x * v.z;
    res.z = this->x * v.y - this->y * v.x;

    return (res);
}

Vertex Vertex::operator*(float num) {
    Vertex res(this->x*num,this->y*num,this->z*num);
    return res;
}

Vertex Vertex::operator+(float num) {
    Vertex res(this->x+num,this->y+num,this->z+num);
    return res;
}

Vertex Vertex::operator-(float num) {
    Vertex res(this->x-num,this->y-num,this->z-num);
    return res;
}

void Vertex::mult(float num) {
    x = x * num;
    y = y * num;
    z = z * num;
}

void Vertex::sum(float num) {
    x = x + num;
    y = y + num;
    z = z + num;
}

void Vertex::sub(float num) {
    x = x - num;
    y = y - num;
    z = z - num;
}

void Vertex::normalize() {
    float aux = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    x = x / aux;
    y = y / aux;
    z = z / aux;
}

void Vertex::dump() {
    cout.precision(2);
    cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

float Vertex::distance(Vertex* v2) {
    return sqrt(pow(this->x - v2->x, 2) + pow(this->y - v2->y, 2) + pow(this->z - v2->x, 2));
}

float Vertex::inner_product(Vertex *v) {
    return (this->x*v->x + this->y*v->y + this->z*v->z) ;
}