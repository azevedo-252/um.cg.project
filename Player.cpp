#include "Player.h"
#include "InputManager.h"
#include "GLManager.h"
#include "Config.h"

#include "externs.h"
#include "Frame.h"

#include <math.h>

extern Config conf;

using namespace std;

Player::Player (const string &path) : Model_MD2(path) {
	coords = new Vertex();
	coords->x = GLManager::distance(conf.rfloat("player:x"));
	coords->z = GLManager::distance(conf.rfloat("player:z"));
	
	direction = new Vertex(0,0,1);
	ang_x = 0;
	ang_y = 0;
	md2_rendermode = 0;

	speed_front	= GLManager::distance(conf.rfloat("player:speed_front"));
	speed_back	= GLManager::distance(conf.rfloat("player:speed_back"));
	speed_side	= GLManager::distance(conf.rfloat("player:speed_side"));
	speed_rotate_x = conf.rfloat("player:speed_rotate_x");
	speed_rotate_y = conf.rfloat("player:speed_rotate_y");


    anim = new Frame();
    anim->add_anim(MOVE_NONE, conf.rint("player:stop_frame"), conf.rint("player:stop_frame_end"));
    anim->add_anim(MOVE_WALK, conf.rint("player:walk_frame"), conf.rint("player:walk_frame_end"));

    //glutTimerFunc(g_anims_interval, GLManager::updateFrames, 0);
}

void Player::move(Vertex *new_coords) {
    coords->x += new_coords->x;
    coords->y += new_coords->y;
    coords->z += new_coords->z;
}

bool Player::isMoving() {
	int w = InputManager::getKeyState(KEY_W);
	int a = InputManager::getKeyState(KEY_A);
	int d = InputManager::getKeyState(KEY_D);
	int s = InputManager::getKeyState(KEY_S);

	return w == KEY_ON || a == KEY_ON || d == KEY_ON || s == KEY_ON;
}

void Player::update() {

    int w = InputManager::getKeyState(KEY_W);
    int a = InputManager::getKeyState(KEY_A);
    int d = InputManager::getKeyState(KEY_D);
    int s = InputManager::getKeyState(KEY_S);

    int m_x = InputManager::getKeyState(MOUSE_X);
    int m_y = InputManager::getKeyState(MOUSE_Y);

    int m_off_x = InputManager::getKeyState(MOUSE_OFF_X);
    int m_off_y = InputManager::getKeyState(MOUSE_OFF_Y);
    ang_x += m_off_x * 2 * M_PI / g_win_w * speed_rotate_x;
    ang_y += m_off_y * 2 * M_PI / g_win_h * speed_rotate_y;

    if (ang_x > 2.0 * M_PI)
        ang_x -= 2.0 * M_PI;
    else if (ang_x < -2.0 * M_PI)
        ang_x += 2.0 * M_PI;

    if (ang_y >= M_PI - 0.5)
        ang_y = M_PI - 0.5;
    else if (ang_y < 0.5)
        ang_y = 0.5;

    this->direction = new Vertex(sin(ang_y) * cos(ang_x),
            cos(ang_y),
            sin(ang_y) * sin(ang_x));

    if (w == KEY_ON) {
        coords->x += speed_front * direction->x;
        coords->z += speed_front * direction->z;
    } else if (s == KEY_ON) {
        coords->x -= speed_back * direction->x;
        coords->z -= speed_back * direction->z;
    }
    if (a == KEY_ON) {
        coords->x += speed_side * direction->z;
        coords->z -= speed_side * direction->x;
    } else if (d == KEY_ON) {
        coords->x -= speed_side * direction->z;
        coords->z += speed_side * direction->x;
    }

    if (isMoving()) {
		coords->y = g_map->triangulateHeight(coords->x, coords->z);
    	if (anim->get_anim() != MOVE_WALK)
    		anim->set_anim(MOVE_WALK);
    }
    else {
    	anim->set_anim(MOVE_NONE);
    }

	
    g_map->adjustPlayableCoords(coords);
}

void Player::render() {
    glPushMatrix();
    glTranslatef(coords->x, coords->y, coords->z);
    glRotatef((-ang_x * 180 / M_PI) + 90, 0, 1, 0);
    md2_model->drawPlayerFrame(anim->get_frame(), static_cast<Md2Object::Md2RenderMode> (md2_rendermode));
    glPopMatrix();
}

void Player::inc_frame(int val) {
	glutTimerFunc(g_anims_interval, Player::inc_frame, 0);
	g_player->anim->inc_frame();
}
