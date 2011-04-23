/* 
 * File:   Radar.cpp
 * Author: gabriel
 * 
 * Created on 9 de Abril de 2011, 18:00
 */


#include "Radar.h"
#include "GLManager.h"
#include "externs.h"

using namespace std;

Radar::Radar() {
    screen_coords = new Vertex(10, 10, 0);
    dist = 0;
    range = GLManager::distance(conf.rfloat("hud:radar_range"));
}

void Radar::set_pos(Vertex* new_coords) {
    screen_coords->x += new_coords->x;
    screen_coords->y += new_coords->y;
    screen_coords->z += new_coords->z;
}

void Radar::update() {
    dist = g_keys->get_closest_distance();
}

void Radar::setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);
    glScalef(1, -1, 1);
    glTranslatef(0, -200, 0);
    glMatrixMode(GL_MODELVIEW);
}

void Radar::resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Radar::render() {
    glPushMatrix();
    glLoadIdentity();
    setOrthographicProjection();
    glRasterPos2i(screen_coords->x, screen_coords->y);
    char *string = new char[50];

    if (g_keys->keys_left == 0)
    	sprintf(string, "All keys catched. GO FOR THE TOILET!");
    else if (dist > range)
    	sprintf(string, "Distance: > 500 meters");
    else
    	sprintf(string, "Distance: %.4f", GLManager::meters(dist));

    int len, i;
    len = strlen(string);
    glColor3f(0, 0, 0);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
    resetPerspectiveProjection();
    glColor3f(1, 1, 1);
    glPopMatrix();
}
