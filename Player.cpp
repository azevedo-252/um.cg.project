#include "Player.h"
#include "InputManager.h"
#include "GLManager.h"
#include "Config.h"

#include "externs.h"
#include "Frame.h"

#include <math.h>

extern Config conf;

using namespace std;

Player::Player(const string &path) : Model_MD2(path) {
	state = GAME_ON;
	coords = new Vertex();
	coords->x = GLManager::distance(conf.rfloat("player:x"));
	coords->z = GLManager::distance(conf.rfloat("player:z"));
	coords->y = g_map->triangulateHeight(coords->x, coords->z);
	direction = new Vertex(0, 0, 1);
	ang_x = 0;
	ang_y = M_PI / 2;
	md2_rendermode = 0;

	speed_front = GLManager::convertFromKmH(conf.rfloat("player:speed_front"));
	speed_back = GLManager::convertFromKmH(conf.rfloat("player:speed_back"));
	speed_side = GLManager::convertFromKmH(conf.rfloat("player:speed_side"));
	speed_rotate_x = conf.rfloat("player:speed_rotate_x");
	speed_rotate_y = conf.rfloat("player:speed_rotate_y");


	anim = new Frame();
	anim->add_anim(MOVE_NONE, conf.rint("player:stop_frame"), conf.rint("player:stop_frame_end"));
	anim->add_anim(MOVE_WALK, conf.rint("player:walk_frame"), conf.rint("player:walk_frame_end"));
	anim->add_anim(MOVE_JUMP, conf.rint("player:jump_frame"), conf.rint("player:jump_frame_end"));

	jump_max = conf.rint("player:jump_max");
	isJumping = false;
	jump_time = 0;
	canJump = true;
	jump_cooldown = conf.rint("player:jump_cooldown");

	tower_colision_dist = conf.rint("player:tower_colision_dist");
	tree_colision_dist = conf.rint("player:tree_colision_dist");
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
	int space = InputManager::getKeyState(KEY_SPACE);

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

	if (state == GAME_ON) {
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
	}

	if (space == KEY_ON && !isJumping && canJump) {
		isJumping = true;
		jump_time = 0;
		Sound::play(SOUND_JUMP);
	}

	if (isJumping) {
		jump_time++;
		coords->y += jumpOff(jump_time) - jumpOff(jump_time - 1);
		if (anim->get_anim() != MOVE_JUMP)
			anim->set_anim(MOVE_JUMP);

		float max_height = g_map->triangulateHeight(coords->x, coords->z);
		if (coords->y < max_height) {
			coords->y = max_height;
			isJumping = false;
			anim->set_anim(MOVE_NONE);
			canJump = false;
			glutTimerFunc(jump_cooldown, GLManager::allowPlayerJump, 0);
		}

	} else if (isMoving()) {
		coords->y = g_map->triangulateHeight(coords->x, coords->z);
		if (anim->get_anim() != MOVE_WALK)
			anim->set_anim(MOVE_WALK);

	} else {
		anim->set_anim(MOVE_NONE);
	}

	g_map->adjustPlayableCoords(coords);
}

float Player::jumpOff(int off) {
	//return - pow(off - jump_max, 2) + pow(jump_max, 2);
	return 0.1 * (-0.5 * pow(off, 2) + 20 * off);
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

void Player::calcColisions() {
	//colisoes com as torres
	for (int i = 0; i < g_towers->num_towers; i++) {
		float dist = this->coords->horizontalDistance(g_towers->towers[i]->coords);
		if (dist < tower_colision_dist) {
			float ang = g_towers->towers[i]->ang_x;
			coords->x = (g_towers->towers[i]->coords->x + tower_colision_dist * cos(-ang));
			coords->z = (g_towers->towers[i]->coords->z + tower_colision_dist * sin(-ang));
		}
	}
	
	//colisoes com as arvores
	for (int i = 0; i < g_trees->num_trees; i++) {
		float dist = this->coords->horizontalDistance(g_trees->trees[i]->coords);
		if (dist < tree_colision_dist) {
			Vertex *direction = g_trees->trees[i]->coords->directionVector(this->coords);
			//direction->x = -direction->x;
			//direction->z = -direction->z;
			float ang = acos(direction->x / dist);
			if (this->coords->z <= g_trees->trees[i]->coords->z)
				ang = -ang;
			coords->x = (g_trees->trees[i]->coords->x + tree_colision_dist * cos(-ang));
			coords->z = (g_trees->trees[i]->coords->z + tree_colision_dist * sin(ang));
		}
	}
}
