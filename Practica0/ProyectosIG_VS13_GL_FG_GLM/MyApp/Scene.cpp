#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  
  camera->setAZ();
    
  // lights
  // textures  

  // objets
  objetos.push_back(new EjesRGB(0, 0, 200.0));
  //objetos.push_back(new Triangulo(0, 0, 200.0));
  //objetos.push_back(new TrianguloRGB(400, 300, 200.0));
  //objetos.push_back(new TriPyramid(400, 0, 200.0, 200.0));
  //objetos.push_back(new ContCubo(0, 300, 200.0));

  objetos.push_back(new Diabolo(0, 0, 200.0, 300.0));
  objetos.push_back(new Dragon(400, 300, 3000));
  objetos.push_back(new Cubo(400, 0, 200.0));
  glm::dvec2 verIni(0, 0);
  objetos.push_back(new Espiral(0, 300, verIni, 0, 45, 1, 1, 50));
  
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
  glMatrixMode(GL_MODELVIEW);
  viewPort->setSize(400, 300);

	for each (Entity* it in objetos)
	{
		viewPort->setPosition(it->getX(), it->getY());
		it->render(camera->getViewMat());
	}
}
//-------------------------------------------------------------------------
