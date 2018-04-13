#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
	 w = aw; 
	 h = ah; 
	 set(); 
 }
 //-------------------------------------------------------------------------
 void Viewport::setPosition(GLint ax, GLint ay)
 {
	 x = ax;
	 y = ay;
	 set();
 }
 //--------------------------------------------------------------------------------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
//-------------------------------------------------------------------------

void Camera::setAZ() 
{
  eye = dvec3(0, 0, 500);
  look = dvec3(0, 0, 0);
  up = dvec3(0, 1, 0);

  front = -normalize(eye - look);
  right = normalize(cross(up, -front));

  pitch_ = 0;
  yaw_ = 0;

  viewMat = lookAt(eye, eye + front, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye= dvec3(500, 500, 500);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);

  front = -normalize(eye - look);
  right = normalize(cross(up, -front));

  pitch_ = degrees(asin(front.y));
  yaw_ = degrees(asin(front.x) / cos(radians(pitch_)));

  viewMat = lookAt(eye, eye + front, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	rotatePY(a, 0);
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a)
{
	rotatePY(0, a);
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs)
{
	eye += right * cs;
	viewMat = lookAt(eye, eye + front, up);
}
//-------------------------------------------------------------------------

void Camera::moveUD(GLdouble cs)
{
	eye += up * cs;
	viewMat = lookAt(eye, eye + front, up);
}
//-------------------------------------------------------------------------

void Camera::moveFB(GLdouble cs)
{
	eye += front * cs;
	viewMat = lookAt(eye, eye + front, up);
}

//-------------------------------------------------------------------------

void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw)
{
	pitch_ += incrPitch;
	yaw_ += incrYaw; // Actualizar los ángulos

	if (pitch_ > 89.5) pitch_ = 89.5; // Limitar los ángulos
	else if (pitch_ < -89.5) pitch_ = -89.5;

	if (yaw_ >= 360) yaw_ -= 360;

	// Actualizar la dirección de vista
	front.x = sin(radians(yaw_)) * cos(radians(pitch_));
	front.y = sin(radians(pitch_));
	front.z = -cos(radians(yaw_)) * cos(radians(pitch_));
	front = glm::normalize(front);

	right = normalize(cross(up, -front));

	viewMat = lookAt(eye, eye + front, up);
}

void Camera::setPrj()
{
	orto = !orto;
	setPM();
}

//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
  if (orto)
  {
	  glMatrixMode(GL_PROJECTION);
	  projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal); //En coordenadas de la cámara
	  glLoadMatrixd(value_ptr(projMat));
	  glMatrixMode(GL_MODELVIEW);
  }
  else
  {
	  nearVal = yTop;
	  glMatrixMode(GL_PROJECTION);
	  projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal); // Plano cercano Distancias al ojo
	  glLoadMatrixd(value_ptr(projMat));
	  glMatrixMode(GL_MODELVIEW);
  }
}
//-------------------------------------------------------------------------


