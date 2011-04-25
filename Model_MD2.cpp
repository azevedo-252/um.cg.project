/**
 * MD2Model.cpp
 */

#include "Model_MD2.h"

Model_MD2::Model_MD2(const string &path) {

    char *ini = (char *) "resources:models_path";
    string dirname(conf.rstring(ini));
    dirname.append(path);

    if (dirname.find_last_of('/') == dirname.length() - 1)
        dirname.assign(dirname, 0, dirname.find_last_of('/'));

    // Get base dir for player if a *.md2 file is given
    if (dirname.find(".md2") == dirname.length() - 4)

#ifdef _WIN32
        dirname.assign(dirname, 0, dirname.find_last_of('\\'));
#else
        dirname.assign(dirname, 0, dirname.find_last_of('/'));
#endif

    md2_model = new Md2Player(dirname);
	this->set_scale(0.25);
}

void Model_MD2::set_scale(GLfloat _scale) {
    md2_model->setScale(_scale);
}