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

#include "externs.h"
#include "Radar.h"

namespace GLManager {

    void init(int *argc, char **argv) {
    	srand(time(NULL));
        /** inicializacao do openGL */
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(conf.rint("window:width"), conf.rint("window:height"));

        char *win_title = strdup(conf.rstring("window:title").c_str());
        glutCreateWindow(win_title);
        free(win_title);

        /* inicializacao do DevIL */
        ilInit();

        /** inicializacao do openAL */
        alutInit(argc, argv);

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
        glEnable(GL_CULL_FACE);

        /** activa a iluminacao */
        //glEnable(GL_LIGHTING);
        //glEnable(GL_LIGHT0);

        /** da main do md2loader */
        glShadeModel(GL_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glCullFace(GL_BACK);

        //glutSetCursor(GLUT_CURSOR_NONE);

        game_init();

        glutSetCursor(GLUT_CURSOR_NONE);
    }

    void game_init() {
    	g_dist_factor = conf.rfloat("game:distance_factor");
    	g_update_interval = 1000 / conf.rint("game:updates_per_second");
    	g_anims_interval  = 1000 / conf.rint("game:anims_per_second");

        Textures::load();
        Sound::load();
        InputManager::init();
        g_camera = new Camera();
        g_map = new Map();
        g_player = new Player(conf.rstring("models:player"));
        g_towers = new Towers();
        g_keys = new Keys();
        g_skybox = new SkyBox();

        g_radar = new Radar();
        //g_profiler = new Profiler();
        
        g_rainbow = new Rainbow();
        g_toilet = new Toilet(conf.rstring("models:toilet"));
    	Sound::play(SOUND_MAIN);
        glutTimerFunc(g_update_interval, update, 0);
    }

    void reshapeFunc(int w, int h) {
        // Prevent a divide by zero, when window is too short
        // (you cant make a window with zero width).
        if (h == 0)
            h = 1;

        // compute window's aspect ratio
        float ratio = w * 1.0 / h;

        // Reset the coordinate system before modifying
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);

        // Set the correct perspective
        gluPerspective(45, ratio, 1, 10000);

        // return to the model view matrix mode
        glMatrixMode(GL_MODELVIEW);

        g_win_w = glutGet(GLUT_WINDOW_WIDTH);
        g_win_h = glutGet(GLUT_WINDOW_HEIGHT);
        g_win_half_w = g_win_w / 2;
        g_win_half_h = g_win_h / 2;
    }

    void render(void) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /**
         * @TODO draw stuff here
         */
        g_map->render();
        g_rainbow->render();
        g_radar->render();
        //g_profiler->render();

        /** tudo o que seja MD2 deve ficar aqui, depois dos outros, para nao estragar as cores */
        g_player->render();
        g_towers->render();
        g_keys->render();
        g_skybox->render();

        InputManager::resetMouseMove();
        // End of frame
        glutSwapBuffers();
    }

    void update(int val) {

    	glutTimerFunc(g_update_interval, update, 0);
    	g_player->update();
    	g_camera->placeCamera();
    	g_towers->update();
    	g_keys->update();
    	g_radar->update();
    	g_rainbow->update();

    	glutPostRedisplay();
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
};
