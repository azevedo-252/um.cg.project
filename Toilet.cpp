#include "Toilet.h"

using namespace std;

#include "externs.h"

Toilet::Toilet(const string &path) : Model_MD2(path) {

    coords = NULL;
    md2_rendermode = 0;
    set_scale(5);
}

void Toilet::render() {
    glPushMatrix();
    md2_model->drawPlayerItp(true, static_cast<Md2Object::Md2RenderMode> (md2_rendermode));
    glPopMatrix();
}

