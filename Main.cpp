
#include <GL/glut.h>

#include "Config.h"
#include "GLManager.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "Tower.h"
#include "Keys.h"
#include "Towers.h"
#include "Rainbow.h"
#include "Toilet.h"
#include "Radar.h"
#include "Sound.h"
#include "SkyBox.h"

//configuracoes principais
Config conf("config.ini");
//instancia do jogador principal
Player* g_player;
Towers* g_towers;
Keys* g_keys;
//instancia do mapa
Map* g_map;
//instancia da camera
Camera* g_camera;
Rainbow* g_rainbow;
Toilet* g_toilet;

SkyBox *g_skybox;

Radar *g_radar;

/* armazenam o tamanho da janela */
int g_win_w, g_win_h, g_win_half_w, g_win_half_h;

/* normalizacao das distancias */
float g_dist_factor;

/* animacoes independentes da framerate */
int g_update_interval;
int g_anims_interval;

int main(int argc, char **argv) {
	GLManager::init(&argc, argv);
	glutMainLoop();
	return 0;
}
