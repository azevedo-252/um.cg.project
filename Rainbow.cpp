#include "Rainbow.h"
#include "InputManager.h"
#include "Config.h"

#include <math.h>
#include "GLManager.h"
#include "externs.h"

using namespace std;

Rainbow::Rainbow () {
	win_distance = conf.rint("game:win_distance");
	win_height = conf.rint("game:win_height");
	win = false;
	float min_dist = conf.rfloat("game:rainbow_min_distance");

	coords = new Vertex(g_map->width, 0, g_map->width);
	ang_x = 45;
	g_map->adjustPlayableCoords(coords);
	coords->y = g_map->triangulateHeight(coords->x, coords->z);
}

void Rainbow::render() {
	GLfloat mat_ambient[4];
	
	glPushMatrix ();
		glTranslatef (coords->x, coords->y, coords->z);
		
		
		glRotatef(ang_x, 0, 1, 0);
		glScalef(0.25, 0.25, 0.25);
		
        g_toilet->render();
		
		// violeta
		mat_ambient[0] = 0.5; mat_ambient[1] =  0.0; mat_ambient[2] = 0.5; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,240,100,100);
		// indigo
		mat_ambient[0] = 0.2; mat_ambient[1] =  0.0; mat_ambient[2] = 0.8; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,250,100,100);
		// azul
		mat_ambient[0] = 0.0; mat_ambient[1] =  0.0; mat_ambient[2] = 1.0; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,260,100,100);
		// verde
		mat_ambient[0] = 0.0; mat_ambient[1] =  1.0; mat_ambient[2] = 0.0; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,270,100,100);
		// amarelo
		mat_ambient[0] = 1.0; mat_ambient[1] =  1.0; mat_ambient[2] = 0.0; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,280,100,100);
		// laranja
		mat_ambient[0] = 1.0; mat_ambient[1] =  0.5; mat_ambient[2] = 0.0; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,290,100,100);
		// vermelho
		mat_ambient[0] = 1.0; mat_ambient[1] =  0.0; mat_ambient[2] = 0.0; mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
		glutSolidTorus(10,300,100,100);
		glColor3f(1, 1, 1);  // -> Porque ?
		
		GLManager::resetMaterials();

	glPopMatrix ();
}

void Rainbow::update() {
	if (g_keys->keys_left == 0 && !win) {
		direction = this->coords->directionVector(g_player->coords);
		dir_dist = (sqrt(pow(direction->x, 2) + pow(direction->z, 2)));

		if (dir_dist < win_distance && g_player->coords->y > this->coords->y + win_height) {
			win = true;
			Sound::stop(SOUND_MAIN);
			Sound::play(SOUND_WIN);
			g_player->state = GAME_WIN;
		}
	}
}
