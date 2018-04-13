#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH/* |
	  GLUT_STENCIL*/);
  camera->setAZ();
    
  // lights
  // textures  

  // objets
  //objetos.push_back(new EjesRGB(0, 0, 200.0));
  //objetos.push_back(new Triangulo(0, 0, 200.0));
  //objetos.push_back(new TrianguloRGB(400, 300, 200.0));
  //objetos.push_back(new TriPyramid(400, 0, 200.0, 200.0));
  //objetos.push_back(new ContCubo(0, 300, 200.0));
  //objetos.push_back(new Diabolo(0, 0, 200.0, 300.0));
 // objetos.push_back(new Dragon(400, 300, 3000));
 // objetos.push_back(new Cubo(400, 0, 200.0));
 // glm::dvec2 verIni(0, 0);
 // objetos.push_back(new Espiral(0, 300, verIni, 0, 60, 0.5, 0.5, 100));

 // objetos.push_back(new RectangleText(0, 0, 200));
  objetos.push_back(new CuboText(0, 0, 200));
  objetos.push_back(new DiaboloText(0, 0, 200.0, 300.0));
  objetos.push_back(new GenerateFloorText(0, 0, 2000, 8, 8));
  objetos.push_back(new Foto(0, 0, 200));
  objetos.push_back(new Grass(0, 0, 200));
  objetos.push_back(new GlassPot(0, 0, 200));
  
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
}
//-------------------------------------------------------------------------

void Scene::render()
{
  glMatrixMode(GL_MODELVIEW);
  //viewPort->setSize(400, 300);

	for each (Entity* it in objetos)
	{
		viewPort->setPosition(it->getX(), it->getY());
		it->render(camera->getViewMat());
	}
}

Entity * Scene::getDiabolo()
{
	std::vector<Entity*>::iterator it = objetos.begin();
	bool diaEncontrado = false;
	while (it != objetos.end() && !diaEncontrado)
	{
		Diabolo* diabolo = dynamic_cast<Diabolo*>(*it);
		if (diabolo == nullptr) {
			DiaboloText* diabolo = dynamic_cast<DiaboloText*>(*it);
			if (diabolo != nullptr) {
				diaEncontrado = true;
			}
			else
			{
				it++;
			}
		}
		else{
			diaEncontrado = true;
		}
	}

	return (*it);
}
//-------------------------------------------------------------------------
