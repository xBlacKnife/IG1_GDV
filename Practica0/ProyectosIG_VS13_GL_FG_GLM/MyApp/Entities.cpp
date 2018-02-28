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

void Espiral::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
