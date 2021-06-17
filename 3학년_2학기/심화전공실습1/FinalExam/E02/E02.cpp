#include "glSetup.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES		//To include the definition of M_PI in math.h
#endif

#include <glm/glm.hpp>				//OpenGL Mathematics
#include <glm/gtc/type_ptr.hpp>		//value_ptr()
using namespace glm;

#include <iostream>
#include <fstream>
using namespace std;

void init();
void quit();
void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);

//Camera configuration
vec3 eyeFrontView(0, 0, 10);	//Front view
vec3 upFrontView(0, 1, 0);		//Front view
vec3 center(0, 0, 0);

//Light configuration
vec4 lightInitialP(0.0, 0.0, 0.8, 1);	//Initial light position

//Global coordinate frame
bool axes = true;

float AXIS_LENGTH = 1.25;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//control variable
int		selection = 1;		//Selected example

//Paly configuration
bool pause = true;

float timeStep = 1.0f / 120; //120fps
float period = 4.0f;

//Current frame
int frame = 0;

int main(int argc, char* argv[]) {
	//vsync should be 0 for precise time stepping
	vsync = 0;

	//Field of view of 85mm lens in degree
	fovy = 16.1f;

	//Initialize the OpenGL system
	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL) return -1;

	//Callbacks
	glfwSetKeyCallback(window, keyboard);

	//Depth test
	glEnable(GL_DEPTH_TEST);

	//Normal vectors are normalized after transformation
	glEnable(GL_NORMALIZE);

	//Viewport and perspective setting
	reshape(window, windowW, windowH);

	//Initialization - Main loop - Finalizaion
	//
	init();

	//Main loop
	float previous = (float)glfwGetTime();
	float elapsed = 0;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();		//Events

		//Time passed during a single loop
		float now = (float)glfwGetTime();
		float delta = now - previous;
		previous = now;

		//Time passed after the previous frame
		elapsed += delta;

		//Deal with the current frame
		if (elapsed > timeStep) {
			//Animate 1 frame
			if (!pause)	frame += 1;

			elapsed = 0;	//Reset the elapsed time
		}

		render(window);				//Draw one frame
		glfwSwapBuffers(window);	//Swap buffers
	}

	//Finalization
	quit();

	//Terminate the glfw system
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

//Sphere, cylinder
GLUquadricObj* sphere = NULL;

void init()
{
	//Prepare quadric shapes
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricTexture(sphere, GL_FALSE);

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: up for increasing highlight" << endl;
	cout << "Keyboard Input: down for decreasing highlight" << endl;
	cout << endl;
	cout << "Keyboard Input: 1 for ambient reflection only" << endl;
	cout << "Keyboard Input: 2 for ambient, diffuse" << endl;
	cout << "Keyboard Input: 3 for ambient, diffuse, specular" << endl;
	cout << "Keyboard Input: 4 for ambient, diffuse, specular and up/down·Î highlight Á¶Àý" << endl;
}

void quit()
{
	//Delete quadric shapes
	gluDeleteQuadric(sphere);
}

float temp = 0.5f;

GLfloat mat_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
//GLfloat mat_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_shininess = 100;

void setupWhiteShinyMaterial()
{
	
	if (selection == 1) {
		mat_ambient[0] = 1.0f;
		mat_diffuse[0] = 0.0f;
		mat_specular[0] = 0.0f;
	}
	else if (selection == 2) {
		mat_ambient[0] = 1.0f;
		mat_diffuse[0] = 0.6f;
		mat_specular[0] = 0.0f;
	}
	else if (selection == 3) {
		mat_ambient[0] = 1.0f;
		mat_diffuse[0] = 0.6f;
		mat_specular[0] = 0.4f;
	}
	else if (selection == 4) {
		mat_ambient[0] = 1.0f;
		mat_diffuse[0] = 0.6f;
		mat_specular[0] = 0.4f;
	}
	//Material
	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

//Light
void setupLight(const vec4& p)
{
	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat specular[4] = { temp, temp, temp, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(p));
}


void setupBrassMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.33f, 0.22f, 0.33f, 1.0f };
	GLfloat mat_diffuse[4] = { 0.78f, 0.57f, 0.11f, 1.0f };
	GLfloat mat_specular[4] = { 0.99f, 0.91f, 0.81f, 1.0f };
	GLfloat mat_shininess = 27.8f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}


void setupRedPlasticMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.3f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[4] = { 0.6f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[4] = { 0.8f, 0.6f, 0.6f, 1.0f };
	GLfloat mat_shininess = 32.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void drawSquare()
{
	//Square
	glBegin(GL_QUADS);

	//front
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glEnd();
}

//Draw a sphere using a GLU quadric
void drawSphere(float radius, int slices, int stacks)
{
	gluSphere(sphere, radius, slices, stacks);
}

//Compute the rotation axis and angle from a to b
//
//Axis is not normalized.
//theta is represented in degrees.
//
/*void computeRotation(const vec3& a, const vec3& b, float& theta, vec3& axis)
{
	axis = cross(a, b);
	float	sinTheta = length(axis);
	float	cosTheta = dot(a, b);
	theta = float(atan2(sinTheta, cosTheta) * 180.0 / M_PI);
}*/


void drawArrow(const vec3& p, bool tailOnly)
{
	//Make it possible to change a subset of material parameters
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//Common material
	GLfloat mat_specular[4] = { 1, 1, 1, 1 };
	GLfloat mat_shininess = 25;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	//Transformation
	glPushMatrix();

	glTranslatef(p.x, p.y, p.z);

	//Tail sphere
	float	arrowTailRadius = 0.05f;
	glColor3f(1, 0, 0);		//ambient and diffuse
	drawSphere(arrowTailRadius, 16, 16);

	glPopMatrix();

	//For convential material setting
	glDisable(GL_COLOR_MATERIAL);
}


void render(GLFWwindow* window)
{
	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	vec3	eye(0), up(0);
	eye = eyeFrontView;	
	up = upFrontView;

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH*dpiScaling);
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//Rotation of the light or 3x3 models
	vec3 axis(0, 1, 0);

	//Lighting
	//
	glEnable(GL_LIGHTING);

	//Set up the lights
	vec4 lightP[3];

	glEnable(GL_LIGHT0);

	setupLight(lightInitialP);

	//Draw the geometries of the lights
	for (int i = 0; i < 1; i++)
	{
		drawArrow(lightP[i], i == 0);	//Tail only for a point light
	}

	//Draw objects
	setupWhiteShinyMaterial();

	glScalef(0.4f, 0.4f, 0.4f);

		vec3	u[3];	//y-axis
		vec3	v[3];	//x-axis
		u[0] = vec3(0, 1, 0) * 2.0f;	u[1] = vec3(0, 0, 0);	u[2] = -u[0];
		v[0] = -vec3(1, 0, 0) * 4.0f;	v[1] = vec3(0, 0, 0);	v[2] = -v[0];

		for (int i = 0; i < 3; i++)
		{
			glPushMatrix();
			glTranslatef(u[i].x, u[i].y, u[i].z);
			//glTranslatef(v[i].x, v[i].y, v[i].z);

			for (int j = 0; j < 3; j++)
			{
				glPushMatrix();

				glTranslatef(v[j].x, v[j].y, v[j].z);
				//glTranslatef(u[j].x, u[j].y, u[j].z);
				//glRotatef(thetaModel, axis.x, axis.y, axis.z);

				drawSphere(0.7f, 64, 64);

				glPopMatrix();
			}
			glPopMatrix();
		}
}

void keyboard(GLFWwindow* window, int key, int scanmode, int action, int mods)
{
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && mods != GLFW_MOD_SHIFT) {
		switch (key)
		{
			//Quit
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

			//Axes
		case GLFW_KEY_X:		axes = !axes; break;

			//Example selection
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;
		case GLFW_KEY_3: selection = 3; break;
		case GLFW_KEY_4: selection = 4; break;

		case GLFW_KEY_UP: temp = min(temp + 0.1f, 1.0f); break;
		case GLFW_KEY_DOWN: temp = max(temp - 0.1f, 0.0f);  break;
		}
	}
}