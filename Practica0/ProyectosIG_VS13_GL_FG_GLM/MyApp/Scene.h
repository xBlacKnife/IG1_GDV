//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "Camera.h"
#include "Entities.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene(Camera* cam, Viewport* view): camera(cam), viewPort(view) { };
	  ~Scene();
    void init();
	void render();

	//Estaría bien hacer un iterador para buscar el diabolo, pero esto es mas sencillo
	//de implementar, si en objetos[1] hay un Entity distinto de diabolo, el programa se
	//quedara colgado
	Entity* getDiabolo() { 
		return objetos[1]; 
	};
	  
protected:
	  Camera* camera;
	  Viewport* viewPort;
	  std::vector<Entity*> objetos;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

