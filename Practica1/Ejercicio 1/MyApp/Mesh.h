//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generateTriangle(GLdouble r);
  static Mesh* generateTriangleRGB(GLdouble r);
  static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
  static Mesh* generateContCubo(GLdouble l);
  static Mesh* generaDragon(GLuint numVert);
  static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, 
	  GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
  static Mesh* generateCuadrado(GLdouble l);
  static Mesh* generateRectangleText(GLdouble l, int repX, int repY);
  static Mesh* generateContCuboText(GLdouble l);
  static Mesh* generateTriPyramidText(GLdouble r, GLdouble h);
 
  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
 

  static glm::dvec2 mover(GLdouble x, GLdouble y, GLdouble ang, GLdouble lon);
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;
   glm::dvec2* texCoords = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_