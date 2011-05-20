/**
 * Classe que gere as configuracoes do OpenGL
 */

#ifndef _glmanager_h
#define _glmanager_h

#include "Vertex.h"

namespace GLManager {

	/** inicia o openGL */
	void init(int *argc, char **argv);

	/** chamada no final de init */
	void game_init();

	/** funcao de resize da janela */
	void reshapeFunc(int w, int h);

	/** funcao de render */
	void render(void);
	
	void resetMaterials(void);

	/** funcao de update dos dados */
	void update(int val);

	/** converte metros para a unidade de OpenGL, conforme */
	float distance(float meters);
	float meters(float distance);

	/** Gera um vertice aleatorio em cima do terreno */
	Vertex* randomVertex();
	
	void updateFrames(int val);
	
	void allowTowerFire(int id);
        
        void allowPlayerJump(int id);
        
        void end_game_test();
};

#endif
