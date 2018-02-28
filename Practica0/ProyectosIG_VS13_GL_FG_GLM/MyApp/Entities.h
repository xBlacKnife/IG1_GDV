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
  virtual void handleEvent(double angle) = 0;

  GLint getX() { return x; };
  GLint getY() { return y; };
  
protected:
  Mesh* mesh = nullptr;
  Mesh* mesh2 = nullptr;
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
  virtual void render(glm::dmat4 const& modelViewMat) {}
  virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------

class Triangulo : public Entity
{
public:
	Triangulo(GLint x, GLint y, GLdouble r);
	~Triangulo() { };
	virtual void draw();
	virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLint x, GLint y, GLdouble r);
	~TrianguloRGB() { };
	virtual void draw();
	virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------

class TriPyramid : public Entity
{
public:
	TriPyramid(GLint x, GLint y, GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
	virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------

class ContCubo : public Entity
{
public:
	ContCubo(GLint x, GLint y, GLdouble l);
	~ContCubo() { };
	virtual void draw();
	virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLint x, GLint y, GLuint numVert);
	~Dragon() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------

class Diabolo : public Entity
{
public:
	Diabolo(GLint x, GLint y, GLdouble r, GLdouble h);
	~Diabolo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void handleEvent(double angle);

private:
	double angle_;
};

//-------------------------------------------------------------------------

class Espiral : public Entity
{
public:
	Espiral(GLint x, GLint y, glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng,
		GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Espiral() { };
	virtual void draw();
	virtual void handleEvent(double angle) {};
};

//-------------------------------------------------------------------------


class Cubo : public Entity
{
public:
	Cubo(GLint x, GLint y, GLdouble l);
	~Cubo() { };
	virtual void draw();
	void drawTop();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void handleEvent(double angle) {}
};

//-------------------------------------------------------------------------


#endif //_H_Entities_H_