/* 
 * File:   Plane.cpp
 * Author: gabriel
 * 
 * Created on May 15, 2011, 6:27 PM
 */

#include "Plane.h"
#include "externs.h"

Plane::Plane(Vertex *v1, Vertex *v2, Vertex *v3) {

    set3Points(v1, v2, v3);

}

void Plane::set3Points(Vertex* v1, Vertex* v2, Vertex* v3) {

    Vertex aux1, aux2;

    aux1 = *v1 - *v2;
    aux2 = *v3 - *v2;

    *normal = aux2 * aux1;

    normal->normalize();

    point = new Vertex(v2->x, v2->y, v2->z);

    d = -(normal->inner_product(point));

}

void Plane::setNormalAndPoint(Vertex* normal, Vertex* point) {
    this->normal = new Vertex ( normal->x, normal->y, normal->z);
    this->normal->normalize();
    d = -(this->normal->inner_product(point));
}

float Plane::distance(Vertex* p) {
    return (d + normal->inner_product(p));
}