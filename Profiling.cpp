/* 
 * File:   Profiling.cpp
 * Author: gabriel
 * 
 * Created on 29 de Abril de 2011, 10:39
 */

#include "Profiling.h"
#include "GLManager.h"
#include "externs.h"

Profiling::Profiling() {
    screen_coords = new Vertex(40, 10, 0);
}

void Profiling::setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);
    glScalef(1, -1, 1);
    glTranslatef(0, -200, 0);
    glMatrixMode(GL_MODELVIEW);
}

void Profiling::resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Profiling::render() {
    glPushMatrix();
    glLoadIdentity();
    setOrthographicProjection();
    glRasterPos2i(screen_coords->x, screen_coords->y);
    char *string = new char[50];

    sprintf(string, "PROFILING: ");

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

