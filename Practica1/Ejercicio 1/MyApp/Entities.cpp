#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLint x, GLint y, GLdouble l): Entity(x, y) 
{
  mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangulo::Triangulo(GLint x, GLint y, GLdouble r) : Entity(x, y)
{
	mesh = Mesh::generateTriangle(r);
}
//-------------------------------------------------------------------------

void Triangulo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLint x, GLint y, GLdouble r) : Entity(x, y)
{
	mesh = Mesh::generateTriangleRGB(r);
}
//-------------------------------------------------------------------------

void TrianguloRGB::draw()
{
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriPyramid::TriPyramid(GLint x, GLint y, GLdouble r, GLdouble h) : Entity(x, y)
{
	mesh = Mesh::generateTriPyramid(r, h);
}
//-------------------------------------------------------------------------

void TriPyramid::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

ContCubo::ContCubo(GLint x, GLint y, GLdouble l) : Entity(x, y)
{
	mesh = Mesh::generateContCubo(l);
}
//-------------------------------------------------------------------------

void ContCubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLint x, GLint y, GLuint numVert) : Entity(x, y)
{
	mesh = Mesh::generaDragon(numVert);
}
//-------------------------------------------------------------------------

void Dragon::draw()
{
	glColor3f(0.0, 0.0, 1.0);

	glPointSize(2);
	mesh->draw();
	glPointSize(1);
}
//-------------------------------------------------------------------------

void Dragon::render(glm::dmat4 const & modelViewMat)
{
	dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(-40.0, -170.0, -300.0));
	aMat = scale(aMat, dvec3(40.0, 40.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}
//-------------------------------------------------------------------------

Diabolo::Diabolo(GLint x, GLint y, GLdouble r, GLdouble h) : Entity(x, y), angle_(0)
{
	mesh = Mesh::generateTriPyramid(r, h);
}
//-------------------------------------------------------------------------

void Diabolo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

void Diabolo::render(glm::dmat4 const & modelViewMat)
{
	
	modelMat = rotate(modelMat, radians(angle_), dvec3(0, 0, 1));
	glMatrixMode(GL_MODELVIEW);

	dmat4 aMat = modelViewMat * modelMat;

	for (int i = 0; i < 2; i++)
	{
		aMat = translate(aMat, dvec3(0.0, 0.0, -300.0));
		glLoadMatrixd(value_ptr(aMat));
		draw();

		aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
		glLoadMatrixd(value_ptr(aMat));
		draw();

		aMat = translate(aMat, dvec3(0.0, 0.0, 300.0));
		aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
	}

	angle_ = 0;
}
//-------------------------------------------------------------------------

void Diabolo::handleEvent(double angle)
{
	angle_ = angle;
}
//-------------------------------------------------------------------------

Cubo::Cubo(GLint x, GLint y, GLdouble l) : Entity(x, y)
{
	mesh = Mesh::generateContCubo(l);
	mesh2 = Mesh::generateCuadrado(l);
}
//-------------------------------------------------------------------------

void Cubo::draw()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

void Cubo::drawTop()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh2->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

void Cubo::render(glm::dmat4 const & modelViewMat)
{
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = modelViewMat * modelMat;
	aMat = rotate(aMat, radians(45.0), dvec3(0, 0, 1));
	aMat = translate(aMat, dvec3(0.0, 142.0, 0.0));
	aMat = translate(aMat, dvec3(100.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	drawTop();

	aMat = modelViewMat * modelMat; //reiniciamos la matriz
	aMat = translate(aMat, dvec3(0.0, -100.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	drawTop();
}
//-------------------------------------------------------------------------

Espiral::Espiral(GLint x, GLint y, glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
	: Entity(x, y)
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

void Espiral::render(glm::dmat4 const & modelViewMat)
{
	dmat4 aMat = modelViewMat * modelMat;

	aMat = scale(aMat, dvec3(5.0, 5.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

void Espiral::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}

//---------------------------------------------------

RectangleText::RectangleText(GLint x, GLint y, GLdouble l, int replicaX, int replicaY) : Entity (x, y)
{
	repX = replicaX;
	repY = replicaY;
	mesh = Mesh::generateRectangleText(l, replicaX, replicaY);
	textura.load("..\\Bmps\\Zelda.bmp");
}

void RectangleText::draw()
{
	textura.bind();

	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);

	textura.unbind();
}

void RectangleText::render(glm::dmat4 const & modelViewMat)
{
	dmat4 aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

//---------------------------------------------------

CuboText::CuboText(GLint x, GLint y, GLdouble l) : Entity(x, y)
{
	mesh = Mesh::generateContCuboText(l);
	mesh2 = Mesh::generateRectangleText(l, 0, 0);
	texturaFuera.load("..\\Bmps\\container.bmp");
	texturaDentro.load("..\\Bmps\\chuches.bmp");

	modelMat = translate(modelMat, dvec3(-200.0, (l / 2) + 1.0, 0.0));
}


void CuboText::draw()
{
	glCullFace(GL_FRONT);
	texturaFuera.bind();
	mesh->draw();
	texturaFuera.unbind();

	glCullFace(GL_BACK);
	texturaDentro.bind();
	mesh->draw();
	texturaDentro.unbind();
}

void CuboText::drawTop()
{
	glCullFace(GL_FRONT);
	texturaFuera.bind();
	mesh2->draw();
	texturaFuera.unbind();

	glCullFace(GL_BACK);
	texturaDentro.bind();
	mesh2->draw();
	texturaDentro.unbind();

}

void CuboText::render(glm::dmat4 const & modelViewMat)
{
	
	glEnable(GL_CULL_FACE);
	
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = modelViewMat * modelMat;
	aMat = rotate(aMat, radians(-225.0), dvec3(0, 0, 1));
	aMat = translate(aMat, dvec3(0.0, -142.0, 0.0));
	aMat = translate(aMat, dvec3(100.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	drawTop();

	aMat = modelViewMat * modelMat; //reiniciamos la matriz
	aMat = translate(aMat, dvec3(0.0, -100.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	drawTop();

	glDisable(GL_CULL_FACE);
	
}

//---------------------------------------------------

DiaboloText::DiaboloText(GLint x, GLint y, GLdouble r, GLdouble h) : Entity(x, y)
{
	mesh = Mesh::generateTriPyramidText(r, h);
	Textura.load("..\\Bmps\\floris.bmp");
	modelMat = translate(modelMat, dvec3(200.0, 200.0, 0.0));
}

void DiaboloText::draw()
{
	Textura.bind();
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	Textura.unbind();
}


void DiaboloText::render(glm::dmat4 const & modelViewMat)
{

	modelMat = rotate(modelMat, radians(angle_), dvec3(0, 0, 1));
	glMatrixMode(GL_MODELVIEW);

	dmat4 aMat = modelViewMat * modelMat;

	for (int i = 0; i < 2; i++)
	{
		aMat = translate(aMat, dvec3(0.0, 0.0, -300.0));
		glLoadMatrixd(value_ptr(aMat));
		draw();

		aMat = rotate(aMat, radians(60.0), dvec3(0, 0, 1));
		glLoadMatrixd(value_ptr(aMat));
		draw();

		aMat = translate(aMat, dvec3(0.0, 0.0, 300.0));
		aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
	}
	
	angle_ = 0;
}

void DiaboloText::handleEvent(double angle)
{
	angle_ = angle;
}

//---------------------------------------------------------

GenerateFloorText::GenerateFloorText(GLint x, GLint y, GLdouble l, int replicaX, int replicaY) : RectangleText(x, y, l, replicaX, replicaY)
{
	mesh = Mesh::generateRectangleText(l, replicaX, replicaY);
	textura.load("..\\Bmps\\baldosaC.bmp");
}

void GenerateFloorText::draw()
{
	textura.bind();
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	textura.unbind();
}

void GenerateFloorText::render(glm::dmat4 const & modelViewMat)
{
	glEnable(GL_REPEAT);
	glEnable(GL_CLAMP);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
	glDisable(GL_REPEAT);
	glDisable(GL_CLAMP);
	
}

//---------------------------------------------------

GlassPot::GlassPot(GLint x, GLint y, GLdouble l) : Entity(x, y)
{
	mesh = Mesh::generateContCuboText(l);
	Textura.load("..\\Bmps\\window.bmp", 150);

	modelMat = translate(modelMat, dvec3(-500.0, (l / 2) + 1.0, -500.0));
}

void GlassPot::draw()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Textura.bind();

	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);

	Textura.unbind();
}

void GlassPot::render(glm::dmat4 const & modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);

	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

	draw();
}

//---------------------------------------------------

Grass::Grass(GLint x, GLint y, GLdouble l) : Entity(x, y)
{
	mesh = Mesh::generateRectangleText(l, 0, 0);
	Textura.load("..\\Bmps\\grass.bmp", {0, 0, 0}, 0);

	modelMat = translate(modelMat, dvec3(-500.0, (l / 2) + 1.0, -500.0));
	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
	modelMat = rotate(modelMat, radians(45.0), dvec3(0, 0, 1));
}

void Grass::draw()
{
	Textura.bind();

	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);

	Textura.unbind();
}

void Grass::render(glm::dmat4 const & modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(90.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	aMat = rotate(aMat, radians(-90.0), dvec3(0, 0, 1));
	glDisable(GL_ALPHA_TEST);
}
