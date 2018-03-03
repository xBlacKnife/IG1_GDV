#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
}
//-------------------------------------------------------------------------

void Mesh::draw() 
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
	
	if (colors != nullptr) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
		
		if (texCoords != nullptr){
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
		}
	}
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m;
}

Mesh * Mesh::generateTriangle(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r * sin(radians(0.0)), r * cos(radians(0.0)), 0.0);
	m->vertices[1] = dvec3(r * sin(radians(120.0)), r * cos(radians(120.0)), 0.0);
	m->vertices[2] = dvec3(r * sin(radians(240.0)), r * cos(radians(240.0)), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generateTriangleRGB(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r * sin(radians(0.0)), r * cos(radians(0.0)), 0.0);
	m->vertices[1] = dvec3(r * sin(radians(120.0)), r * cos(radians(120.0)), 0.0);
	m->vertices[2] = dvec3(r * sin(radians(240.0)), r * cos(radians(240.0)), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generateTriPyramid(GLdouble r, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, 0.0, h);
	m->vertices[1] = dvec3(r * sin(radians(0.0)), r * cos(radians(0.0)), 0.0);
	m->vertices[2] = dvec3(r * sin(radians(120.0)), r * cos(radians(120.0)), 0.0);
	m->vertices[3] = dvec3(r * sin(radians(240.0)), r * cos(radians(240.0)), 0.0);
	m->vertices[4] = dvec3(r * sin(radians(0.0)), r * cos(radians(0.0)), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[4] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generateContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[1] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[2] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[3] = dvec3(l / 2, -l / 2, -l / 2);
	m->vertices[4] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[5] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[6] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[7] = dvec3(-l / 2, -l / 2, l / 2);
	m->vertices[8] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[9] = dvec3(-l / 2, -l / 2, -l / 2);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[4] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[5] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[6] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[7] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[8] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[9] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->type = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, 0.0, 0.0);

	double PR1 = 0.787473;

	for (int i = 1; i < numVert; i++) {
		double azar = rand() / double(RAND_MAX);
		if (azar < PR1) {
			m->vertices[i] = dvec3(0.824074 * m->vertices[i - 1].x + 0.281482 * m->vertices[i - 1].y - 0.882290,
				-0.212346 * m->vertices[i - 1].x + 0.864198 * m->vertices[i - 1].y - 0.110607, 0.0);
		}
		else {
			m->vertices[i] = dvec3(0.088272 * m->vertices[i - 1].x + 0.520988 * m->vertices[i - 1].y + 0.785360,
				-0.463889 * m->vertices[i - 1].x - 0.377778 * m->vertices[i - 1].y + 8.095795, 0.0);
		}
	}

	return m;
}

Mesh * Mesh::generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, 
	GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
		Mesh* m = new Mesh();
		m->type = GL_LINE_STRIP;
		m->numVertices = numVert;
		m->vertices = new dvec3[m->numVertices];
		m->colors = new dvec4[m->numVertices];
		//Vertice inicial
		m->vertices[0] = dvec3(verIni, 0);
		//Los demas vertices
		for (int i = 1; i < numVert; i++)
		{
			m->vertices[i] = dvec3(mover(m->vertices[i - 1].x, m->vertices[i - 1].y, angIni + incrAng * i, ladoIni + incrLado * i), 0);
			m->colors[i] = dvec4(0.0, 0.0, 0.0, 0.0);
		}
		return m;
}

//-------------------------------------------------------------------------

dvec2 Mesh::mover(GLdouble x, GLdouble y, GLdouble ang, GLdouble lon)
{
	return dvec2(x + lon*cos(radians(ang)), y + lon*sin(radians(ang)));
}

//-------------------------------------------------------------------------

Mesh * Mesh::generateCuadrado(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(-l / 2, 0, -l / 2);
	m->vertices[1] = dvec3(-l / 2, 0, l / 2);
	m->vertices[2] = dvec3(l / 2, 0, -l / 2);
	m->vertices[3] = dvec3(l / 2, 0, l / 2);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generateRectangleTex(GLdouble l)
{
	Mesh *m = generateCuadrado(l);

	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);

	return m;
}

Mesh * Mesh::generateCuboTex(GLdouble l)
{
	Mesh *m = generateContCubo(l);

	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);
	m->texCoords[4] = dvec2(0, 1);
	m->texCoords[5] = dvec2(0, 0);
	m->texCoords[6] = dvec2(1, 1);
	m->texCoords[7] = dvec2(1, 0);
	m->texCoords[8] = dvec2(0, 1);
	m->texCoords[9] = dvec2(0, 0);

	return m;
}

//-------------------------------------------------------------------------
