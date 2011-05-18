/* 
 * File:   Profiling.cpp
 * Author: gabriel
 * 
 * Created on May 18, 2011, 1:01 AM
 */

#include "externs.h"
#include "Profiling.h"

Profiling::Profiling() {
    old_count = new_count = glutGet(GLUT_ELAPSED_TIME);
    frames = fps = 0;
    coords = new Vertex(100, -200, 0);
    for(int i = 0; i < TIME_SIZE; i++) {
        name[i] = NULL;
        start[i] = end[i] = 0;
    }
}

void Profiling::update() {
    new_count = glutGet(GLUT_ELAPSED_TIME);
    frames++;
    if (new_count - old_count > 1000) {
        fps = frames * 1000 / (new_count - old_count);
        frames = 0;
        old_count = new_count;
    }
}

void Profiling::setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);
    glScalef(1, -1, 1);
    glTranslatef(coords->x, coords->y, coords->z);
    glMatrixMode(GL_MODELVIEW);
}

void Profiling::resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    coords->y = coords->y + 10;
}


void Profiling::print(char* string) {
    glPushMatrix();
    glLoadIdentity();
    setOrthographicProjection();
    glRasterPos2i(15, 15);

    int len, i;
    len = strlen(string);
    glColor3f(0.0f, 1.0f, 1.0f);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
    resetPerspectiveProjection();
    glColor3f(1, 1, 1);
    glPopMatrix();
}


void Profiling::reset() {
    coords->y = -200;   
    for(int i = 0; i < TIME_SIZE; i++)
        start[i] = end[i] = 0.0;    
}

void Profiling::print_time() {
    char buff[50];
    for(int i = 0; i < TIME_SIZE && start[i] != 0.0; i++) {
        sprintf(buff, "%s: %f", name[i], end[i] - start[i]);
        print(buff);
    }
}

void Profiling::start_time(int num, char* new_name) {
    start[num] = glutGet(GLUT_ELAPSED_TIME);
    if(name[num] == NULL) {
        name[num] = (char *) calloc(50, sizeof(char));
        strcpy(this->name[num],new_name);
    }
}

void Profiling::end_time(int num) {
    end[num] = glutGet(GLUT_ELAPSED_TIME);
}

void Profiling::render() {
    glPushMatrix();
    glLoadIdentity();
    setOrthographicProjection();
    glRasterPos2i(15, 15);
    char *string = new char[50];

    sprintf(string, "FPS: %d", fps);

    int len, i;
    len = strlen(string);
    glColor3f(0.0f, 1.0f, 1.0f);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
    resetPerspectiveProjection();
    glColor3f(1, 1, 1);
    glPopMatrix();
    print_time();
}