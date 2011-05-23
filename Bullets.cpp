/**
 * Bullets.cpp
 */

#include <math.h>

#include "externs.h"
#include "Bullets.h"
#include "Map.h"

int Bullets::anim_start;
int Bullets::anim_end;

Bullets::Bullets(const string &path) {
    anim_start = conf.rint("game:bullet_walk_frame");
    anim_end = conf.rint("game:bullet_walk_frame_end");

    createBulletsLists(path);

}

void Bullets::createBulletsLists(const string &path) {
    int anims = anim_end - anim_start + 1;
    bulletFrames = (GLuint *) malloc(sizeof (GLuint) * anims);

    Model_MD2 *bullet = new Model_MD2(path);
    bullet->md2_rendermode = 0;
    for (int i = 0; i <= anims; i++) {
        bulletFrames[i] = glGenLists(1);
        glNewList(bulletFrames[i], GL_COMPILE);
        bullet->md2_model->drawPlayerFrame(i + anim_start - 1, static_cast<Md2Object::Md2RenderMode> (bullet->md2_rendermode));
        glEndList();
    }
}

void Bullets::update() {
    for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end();) {
        it->update();
        if (!g_map->isPlayableCoords(it->coords)) {
            it = bullets.erase(it);
        } else it++;
    }
}

void Bullets::updateFrames() {
    for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++) {
        it->inc_frame();
    }
}

void Bullets::render() {
    int frame;
    Vertex *coords;
    float ang;

    for (list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++) {
        frame = it->anim->current_frame;
        coords = it->coords;
        ang = it->ang;
        if (g_frustum->sphereInFrustum(new Vertex(coords->x, coords->y + 5, coords->z), 5)) {
            glPushMatrix();
            glTranslatef(coords->x, coords->y, coords->z);
            glRotatef(ang, 0, 1, 0);
            glCallList(bulletFrames[frame - anim_start]);
            //md2_model->drawPlayerFrame(frame, static_cast<Md2Object::Md2RenderMode> (md2_rendermode));
            glTranslatef(0, 5, 0);
            //glutSolidSphere(5, 36, 36);
            glPopMatrix();
        }
    }
}

void Bullets::addBullet(Vertex* coords, float ang, float ang_rad) {
    Bullet *b = new Bullet(coords, ang, ang_rad);
    bullets.push_front(*b);
}

void Bullets::bullet_hit_test() {
    Vertex *c_bullet, *c_player = g_player->coords;
    for (list<Bullet>::iterator it = bullets.begin(); g_lifes->lifes > 0 && it != bullets.end(); it++) {
        c_bullet = it->coords;
        if (sqrt(pow(c_player->x - c_bullet->x, 2) + pow(c_player->y - c_bullet->y, 2) + pow(c_player->z - c_bullet->z, 2)) <= BULLET_HIT_DIST) {
            g_lifes->lifes--;
			it = bullets.erase(it);
			Sound::play(SOUND_LIFE_LOST);
        }
    }
}