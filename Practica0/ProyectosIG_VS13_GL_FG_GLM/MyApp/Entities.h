//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity(GLint x, GLint y) : modelMat(1.0), x(x), y(y) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);

  GLint getX() { return x; };
  GLint getY() { return y; };
  
protected:
  Mesh* mesh = nullptr;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);

private:
	GLint x, y;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLint x, GLint y, GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};

//-------------------------------------------------------------------------

class Triangulo : public Entity
{
public:
	Triangulo(GLint x, GLint y, GLdouble r);
	~Triangulo() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLint x, GLint y, GLdouble r);
	~TrianguloRGB() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class TriPyramid : public Entity
{
public:
	TriPyramid(GLint x, GLint y, GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class ContCubo : public Entity
{
public:
	ContCubo(GLint x, GLint y, GLdouble l);
	~ContCubo() { };
	virtual void draw();
};

//-------------------------------------------------------------------------


#endif //_H_Entities_H_