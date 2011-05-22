#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/ilut.h>
#include <AL/alut.h>
#include <stdlib.h>

#include "Config.h"
#include "GLManager.h"
#include "InputManager.h"
#include "Textures.h"

#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Tower.h"
#include "Towers.h"
#include "Rainbow.h"
#include "Toilet.h"
#include "Trees.h"

#include "externs.h"
#include "Radar.h"

#define PROFILER_START //g_profiling->start_time
#define PROFILER_END //g_profiling->end_time

namespace GLManager {

	void init(int *argc, char **argv) {
		srand(time(0));
		/** inicializacao do openGL */
		glutInit(argc, argv);
		
		//inicial o profiling
		g_profiling = new Profiling();
		g_profiling->start_time(TIME_STARTUP, "Startup");
		
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(conf.rint("window:width"), conf.rint("window:height"));
		glutCreateWindow(conf.rstring("window:title").c_str());

		initGameMode();
		/* inicializacao do DevIL */
		ilInit();

		/** inicializacao do openAL */
		alutInit(argc, argv);

		/* inicializacao do glew */
		glewInit();

		initCallbacks();
	}

	void initCallbacks() {

		/** registo das funcoes de render */
		glutDisplayFunc(render);
		//glutIdleFunc(render);
		glutReshapeFunc(reshapeFunc);

		/** registo das funcoes de teclado e rato */
		glutKeyboardFunc(InputManager::keyboardFunc);
		glutKeyboardUpFunc(InputManager::keyboardUpFunc);
		glutSpecialFunc(InputManager::keyboardSpecialFunc);
		glutMouseFunc(InputManager::mouseButtons);

		/** @TODO: assume-se para ja, que nao ha diferenca entre estas duas
		 * com botoes premidos ou nao, o comportamento do movimento do rato e o mesmo para ja */
		glutMotionFunc(InputManager::mouseMotion);
		glutPassiveMotionFunc(InputManager::mouseMotion);

		/** mais alguns settings */
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_SHADE_MODEL);

		/** inicializacao dos Vertex Buffer Objects */
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		/** activa a iluminacao */
//		glEnable(GL_LIGHTING);
//		glEnable(GL_LIGHT0);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);

		/** da main do md2loader */
		glShadeModel(GL_SMOOTH);
		glEnable(GL_TEXTURE_2D);
		glCullFace(GL_BACK);

		//glutSetCursor(GLUT_CURSOR_NONE);

		game_init();

		glutSetCursor(GLUT_CURSOR_NONE);
		
		g_profiling->end_time(TIME_STARTUP);
	}

	void game_init() {
		g_dist_factor = conf.rfloat("game:distance_factor");
		g_update_interval = 1000 / conf.rint("game:updates_per_second");
		g_anims_interval = 1000 / conf.rint("game:anims_per_second");
		Bullet::speed = conf.rint("game:bullet_speed");
		Tower::bullet_delay = 1000 * conf.rfloat("game:seconds_per_bullet");

		Textures::load();
		Sound::load();
		InputManager::init();
		g_map = new Map();
		g_camera = new Camera();
		g_player = new Player(conf.rstring("models:player"));
		g_towers = new Towers(conf.rstring("models:tower"));
		g_bullets = new Bullets(conf.rstring("models:bullet"));
		g_keys = new Keys();
		g_skybox = new SkyBox();

		g_radar = new Radar();
		//g_profiler = new Profiler();

		g_rainbow = new Rainbow();
		g_toilet = new Toilet(conf.rstring("models:toilet"));
		Sound::play(SOUND_MAIN);
		glutTimerFunc(g_update_interval, GLManager::update, 0);
		glutTimerFunc(g_anims_interval, GLManager::updateFrames, 0);
		g_frustum = new Frustum();
		g_lighting = new Lighting();
		g_lifes = new Lifes();
		g_trees = new Trees();
	}

	void initGameMode() {
		stringstream stream;
		stream << glutGet(GLUT_SCREEN_WIDTH) << 'x' << glutGet(GLUT_SCREEN_HEIGHT) <<
			':' << conf.rint("window:def_window_depth") << '@' << conf.rint("window:def_refresh_rate");

		glutGameModeString(stream.str().c_str());
		if (conf.rint("window:fullscreen") && glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			glutEnterGameMode();
	}

	void reshapeFunc(int w, int h) {
		// Prevent a divide by zero, when window is too short
		// (you cant make a window with zero width).
		if (h == 0)
			h = 1;

		// compute window's aspect ratio
		Camera::persp_ratio = w * 1.0 / h;

		// Reset the coordinate system before modifying
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set the viewport to be the entire window
		glViewport(0, 0, w, h);

		// Set the correct perspective
		gluPerspective(Camera::persp_ang, Camera::persp_ratio, Camera::persp_z_near, Camera::persp_z_far);

		// return to the model view matrix mode
		glMatrixMode(GL_MODELVIEW);

		g_win_w = glutGet(GLUT_WINDOW_WIDTH);
		g_win_h = glutGet(GLUT_WINDOW_HEIGHT);
		g_win_half_w = g_win_w / 2;
		g_win_half_h = g_win_h / 2;

		g_frustum->setCamInternals(g_camera->persp_ang, g_camera->persp_ratio, g_camera->persp_z_near, g_camera->persp_z_far);
	}

	void render(void) {
		g_profiling->start_time(TIME_RENDER_TOTAL, (char *) "Render total");
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_lighting->render();

		g_frustum->setCamDef(g_camera->camPos, g_camera->camDir, g_camera->camUp);
		/**
		 * @TODO draw stuff here
		 */

		g_map->render();

		/** tudo o que seja MD2 deve ficar aqui, depois dos outros, para nao estragar as cores */
		g_player->render();
		g_towers->render();
		g_bullets->render();
		g_keys->render();
		g_skybox->render();

		g_frustum->drawPlanes();
		g_rainbow->render();


		g_trees->render();
		
		glColor3f(1.0, 1, 1);
		g_radar->render();
		g_lifes->render();
		//glDisable(GL_DEPTH_TEST);
		//glEnable(GL_DEPTH_TEST);

//		GLfloat mat_ambient[4];
//		mat_ambient[0] = 0.5;
//		mat_ambient[1] = 0.5;
//		mat_ambient[2] = 0.5;
//		mat_ambient[3] = 1.0;
//		glPushMatrix();
//		glBindTexture(GL_TEXTURE_2D, 0);
//		glTranslatef(conf.rint("player:x"), conf.rint("player:y")+5, conf.rint("player:z"));
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
//		mat_ambient[0] = 0.1;
//		mat_ambient[1] = 0.1;
//		mat_ambient[2] = 0.1;
//		mat_ambient[3] = 0.1;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_ambient);
//		glutSolidSphere(50, 50, 50);
//		glPopMatrix();
//		GLManager::resetMaterials();

		InputManager::resetMouseMove();
		
		g_profiling->end_time(TIME_RENDER_TOTAL);
		g_profiling->update();
		g_profiling->render();
		g_profiling->reset_time();
		// End of frame
		glutSwapBuffers();
	}

	void resetMaterials() {
		GLfloat mat_ambient[4];
		//reset aos materiais
		mat_ambient[0] = 0.2;
		mat_ambient[1] = 0.2;
		mat_ambient[2] = 0.2;
		mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		mat_ambient[0] = 0.8;
		mat_ambient[1] = 0.8;
		mat_ambient[2] = 0.8;
		mat_ambient[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_ambient);
		mat_ambient[0] = 0;
		mat_ambient[1] = 0;
		mat_ambient[2] = 0;
		mat_ambient[3] = 1;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_ambient);
	}

	void update(int val) {

		glutTimerFunc(g_update_interval, update, 0);
		g_player->update();
		g_camera->placeCamera();
		g_towers->update();
		g_bullets->update();
		g_keys->update();
		g_radar->update();
		g_rainbow->update();

		glutPostRedisplay();

		g_bullets->bullet_hit_test();

		g_player->calcColisions();
		end_game_test();
	}

	float distance(float meters) {
		return meters * g_dist_factor;
	}

	float meters(float distance) {
		return distance / g_dist_factor;
	}

	Vertex* randomVertex() {
		return new Vertex(rand() % g_map->width, 0, rand() % g_map->width);
	}

	void updateFrames(int val) {
		glutTimerFunc(g_anims_interval, GLManager::updateFrames, 0);

		if (g_player->isMoving() || g_player->isJumping) {
			g_player->anim->inc_frame();
		}

		g_bullets->updateFrames();
	}

	void allowTowerFire(int id) {
		g_towers->towers[id]->allowFire();
	}

	void allowPlayerJump(int id) {
		g_player->canJump = true;
	}

	void end_game_test() {
		if (g_lifes->lifes <= 0 && g_lifes->hasEnded == false) {
			g_lifes->hasEnded = true;
			//printf("FIM DO JOGO\n");
			Sound::stop(SOUND_MAIN);
			Sound::play(SOUND_GAME_OVER);
			g_player->state = GAME_OVER;
		}
	}
};
