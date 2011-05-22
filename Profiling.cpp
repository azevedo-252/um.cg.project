/* 
 * File:   Profiling.cpp
 * Author: gabriel
 * 
 * Created on May 18, 2011, 1:01 AM
 */

#include <GL/glew.h>

#include "externs.h"
#include "Profiling.h"
#include "ChangeMode.h"

Profiling::Profiling() {
	old_count = new_count = glutGet(GLUT_ELAPSED_TIME);
	frames = fps = 0;
	coords = new Vertex(100, -175, 0);
	for (int i = 0; i < TIME_SIZE; i++) {
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

void Profiling::print(char* string) {
	ChangeMode::setOrthographicProjection();


	glPushMatrix();

	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(g_win_w - 100, g_win_h - 20 - coords->y);

	int len, i;

	len = strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
	}

	coords->y = coords->y + 15;

	glPopMatrix();

	ChangeMode::resetPerspectiveProjection();
}

void Profiling::reset_time() {
	//faz reset a todos excepto ao tempo de startup
	coords->y = 0;
	for (int i = 0; i < TIME_SIZE; i++)
		if (i != TIME_STARTUP)
			start[i] = end[i] = 0.0;
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
	start[num] = glutGet(GLUT_ELAPSED_TIME);
	if (name[num] == NULL) {
		name[num] = (char *) calloc(50, sizeof (char));
		strcpy(this->name[num], new_name);
	}
}

void Profiling::end_time(TIMES num) {
	end[num] = glutGet(GLUT_ELAPSED_TIME);
}

void Profiling::render() {
	print_fps();
	print_time();
}