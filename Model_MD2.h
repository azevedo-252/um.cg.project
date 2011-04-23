/**
 * MD2Model
 */

#ifndef _MODEL_MD2_H
#define _MODEL_MD2_H

#include "Model.h"
#include "md2loader/Md2Player.h"

class Model_MD2 : public Model {
protected:
	Md2Player* md2_model;
	int md2_rendermode;

public:
	Model_MD2(const string &path);
        void set_scale(GLfloat _scale);
};

#endif
