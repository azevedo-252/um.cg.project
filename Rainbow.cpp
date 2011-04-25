#include "Rainbow.h"
#include "InputManager.h"
#include "Config.h"

#include <math.h>
#include "GLManager.h"
#include "externs.h"

using namespace std;

Rainbow::Rainbow () {
	win_distance = conf.rint("game:win_distance");
	win = false;
	float min_dist = conf.rfloat("game:rainbow_min_distance");

	coords = new Vertex(g_map->width, 0, g_map->width);
	ang_x = 45;
	g_map->adjustPlayableCoords(coords);
}

void Rainbow::render() {
	glPushMatrix ();
		glTranslatef (coords->x, coords->y, coords->z);
		glRotatef(ang_x, 0, 1, 0);
		glScalef(0.25, 0.25, 0.25);
		// violeta
		glColor3f(0.5,0.0,0.5); //red, green, blue
		glutSolidTorus(10,240,100,100);
		// indigo
		glColor3f(0.2,0.0,0.8); //red, green, blue
		glutSolidTorus(10,250,100,100);
		// azul
		glColor3f(0.0,0.0,1.0); //red, green, blue
		glutSolidTorus(10,260,100,100);
		// verde
		glColor3f(0.0,1.0,0.0); //red, green, blue
		glutSolidTorus(10,270,100,100);
		// amarelo
		glColor3f(1.0,1.0,0.0); //red, green, blue
		glutSolidTorus(10,280,100,100);
		// laranja
		glColor3f(1.0,0.5,0.0); //red, green, blue
		glutSolidTorus(10,290,100,100);
		// vermelho
		glColor3f(1.0,0.0,0.0); //red, green, blue
		glutSolidTorus(10,300,100,100);
		glColor3f(1, 1, 1);  // -> Porque ?

        g_toilet->render();
	glPopMatrix ();
}

void Rainbow::update() {
	if (g_keys->keys_left == 0 && !win) {
		direction = this->directionVector(g_player->coords);
		dir_dist = (sqrt(pow(direction->x, 2) + pow(direction->z, 2)));

		if (dir_dist < win_distance) {
			win = true;
			Sound::stop(SOUND_MAIN);
			Sound::play(SOUND_WIN);
		}
	}
}
