#ifndef __GL_SETUP_H_
#define __GL_SETUP_H__

#include <Windows.h>
#include <gl/GLU.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

extern float screenScale; //portion of the screen when not using full screen
extern int screenW, screenH; //screenScale portion of the screen
extern int windowW, windowH; //Framebuffer size
extern float aspect; //Aspect ratio = windowW/windowH
extern float dpiScaling; //DPI scaling for HIDPI

extern int vsync; //Vertical sync on/off

extern bool perspectiveView; //Perspective of orthographic viewing
extern float fovy; //Filed of view in the y direction
extern float nearDist; //Near plane
extern float farDist; //Far plane 

GLFWwindow* initializeOpenGL(int argc, char* argv[], GLfloat bg[4]);
void reshape(GLFWwindow* window, int w, int h);
void setupProjectionMatrix();

void drawAxes(float l, float w);

#endif