/* 
 * File:   Profiling.cpp
 * Author: gabriel
 * 
 * Created on May 18, 2011, 1:01 AM
 */

#include "externs.h"
#include "Profiling.h"
#include "ChangeMode.h"

Profiling::Profiling() {
    old_count = new_count = glutGet(GLUT_ELAPSED_TIME);
    frames = fps = 0;
    start_coord_y = 400;
    coords = new Vertex(400, start_coord_y, 0);
    for (int i = 0; i < TIME_SIZE; i++) {
        name[i] = NULL;
        start[i] = end[i] = 0;
    }
    printed = false;
}

void Profiling::update() {
    //int zero = InputManager::getKeyState(KEY_W);
    new_count = glutGet(GLUT_ELAPSED_TIME);
    frames++;
    if (new_count - old_count > 1000) {
        fps = frames * 1000 / (new_count - old_count);
        frames = 0;
        old_count = new_count;
    }
    //    printed = true;
}

void Profiling::print(char* string) {
    ChangeMode::setOrthographicProjection();


    glPushMatrix();

    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(coords->x, coords->y);

    int len, i;

    len = strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }

    coords->y += 30;
    //    glColor3f(1, 1, 1);

    glPopMatrix();

    ChangeMode::resetPerspectiveProjection();
}

void Profiling::reset_time() {
    coords->y = start_coord_y;
//    for (int i = 0; i < TIME_SIZE; i++)
//        start[i] = end[i] = 0.0;

}

void Profiling::print_fps() {
    char string[15];
    sprintf(string, "FPS: %d", fps);
    print(string);
}

void Profiling::print_time() {
    char buff[50];
    for (int i = 0; i < TIME_SIZE && start[i] != 0.0; i++) {
        sprintf(buff, "%s: %d", name[i], end[i] - start[i]);
        print(buff);
    }
}

void Profiling::start_time(TIMES num, char* new_name) {
    if (!printed) {
        start[num] = glutGet(GLUT_ELAPSED_TIME);
        if (name[num] == NULL) {
            name[num] = (char *) calloc(50, sizeof (char));
            strcpy(this->name[num], new_name);
        }
    }
}

void Profiling::end_time(TIMES num) {
    if (!printed) {
        end[num] = glutGet(GLUT_ELAPSED_TIME);
    }
}

void Profiling::render() {
    print_fps();
    print_time();
    printed = true;
}