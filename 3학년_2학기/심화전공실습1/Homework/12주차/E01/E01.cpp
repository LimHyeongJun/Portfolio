#include "glSetup.h"

#include <glm/glm.hpp>				//OpenGL Mathematics
#include <glm/gtc/type_ptr.hpp>		//value_ptr()
using namespace glm;

#include <iostream>
#include <fstream>
using namespace std;

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <math.h>

void init();
void quit();
void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);
void mouseButton(GLFWwindow* window, int button, int action, int mods);
void mouseMove(GLFWwindow* window, double x, double y);

//Camera configuation

vec3	eyeFrontView(0, 0, 10);		//Front view
vec3	upFrontView(0, 1, 0);		//Front view
vec3	center(0, 0, 0);

//Light configuration
vec4	light(0.0, 0.0, 0.8, 1);	//Initial light position

//Global coordinate frame
bool axes = true;
float AXIS_LENGTH = 1.25;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

float rectanglePoint[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
double pickedPoint[2][2] = { {0, 0}, {0, 0} };

int pickedName[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

//Mouse input mode
enum class InputMode {
	NONE = 0,
	DRAGGING = 1,
	COMPLETE = 2,
};

InputMode inputMode = InputMode::NONE;

int main(int argc, char* argv[]) {
	//Field of view of 85mm lens in degree
	fovy = 16.1f;

	perspectiveView = false;

	//Initialize the OpenGL system
	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL) return -1;

	//Callbacks
	glfwSetKeyCallback(window, keyboard);
	glfwSetMouseButtonCallback(window, mouseButton);
	glfwSetCursorPosCallback(window, mouseMove);

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
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();			//Events

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

	//Usage
	cout << endl;
	cout << "Keyboard Input: x for axes on/off" << endl;
	cout << "Mouse button down, dragging and then select objects" << endl;
}

void quit()
{
	//Delete quadric shapes
	gluDeleteQuadric(sphere);
}

//Material
void setupColoredMaterial(const vec3& color)
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { color[0], color[1], color[2], 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess = 100.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

//Draw a sphere using a GLU quadric
void drawSphere(float radius, int slices, int stacks)
{
	gluSphere(sphere, radius, slices, stacks);
}

//Light
void setupLight(const vec4& p)
{
	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(p));
}

void render(GLFWwindow* window)
{
	//Picking
	glInitNames();	//Initialize the name stack
	glPushName(-1);	//Push at least one name in the stack

	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	vec3	eye(0), up(0);

	eye = eyeFrontView;		up = upFrontView;

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		glDisable(GL_LINE_STIPPLE);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH*dpiScaling);
	}

	//Desired position of the end-effector
	if (inputMode == InputMode::DRAGGING) {
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(int(3 * dpiScaling), 0xcccc);
	}
	else glDisable(GL_LINE_STIPPLE);

	if (inputMode == InputMode::DRAGGING) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(rectanglePoint[0][0], rectanglePoint[0][1]);
		glVertex2f(rectanglePoint[1][0], rectanglePoint[1][1]);
		glVertex2f(rectanglePoint[2][0], rectanglePoint[2][1]);
		glVertex2f(rectanglePoint[3][0], rectanglePoint[3][1]);
		glEnd();
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);


	//Lighting
	//
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	setupLight(light);

	//Draw objects
	//
	//3x3 spheres or bunnies
	glScalef(0.4f, 0.4f, 0.4f);

	vec3	u[3];	//y-axis
	vec3	v[3];	//x-axis
	u[0] = vec3(0, 1, 0) * 2.0f;	u[1] = vec3(0, 0, 0);	u[2] = -u[0];
	v[0] = -vec3(1, 0, 0) * 4.0f;	v[1] = vec3(0, 0, 0);	v[2] = -v[0];

	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslatef(u[i].x, u[i].y, u[i].z);
		for (int j = 0; j < 3; j++) {
			glPushMatrix();
			glTranslatef(v[j].x, v[j].y, v[j].z);

			//Material
			if (pickedName[3 * i + j] != -1)	setupColoredMaterial(vec3(0, 0, 1));	//Selected
			else                        setupColoredMaterial(vec3(1, 1, 1));	//Non-selected

			//Picking
			glLoadName(3 * i + j);	//Replace the name for the i-th row, j-th column

			//Draw a sphere
			drawSphere(0.7f, 64, 64);

			glPopMatrix();
		}
		glPopMatrix();
	}
}

void keyboard(GLFWwindow* window, int key, int scanmode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key)
		{
			//Quit
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

			//Axes on/off
		case GLFW_KEY_X: axes = !axes;	break;
		}
	}
}

int findHits(int hits, GLuint selectBuffer[64])
{
	memset(pickedName, -1, sizeof(int) * 9);

	bool	diagnosis = true;

	if (selectBuffer[3] > 8)
		hits--;

	if (diagnosis)	cout << "hits = " << hits << endl;

	if (selectBuffer[3] > 8)
		hits++;

	int		index = 0;
	for (int i = 0; i < hits; i++) {
		int		n = selectBuffer[index];						//# of names

		if (selectBuffer[index + 3] >= 0 && selectBuffer[index + 3] <= 8) {
			cout << "\t# of names = " << n << endl;
			cout << "\tnames: ";
			for (int j = 0; j < n; j++)
				cout << selectBuffer[index + 3 + j] << " ";
			cout << endl;

			pickedName[selectBuffer[index + 3]] = selectBuffer[index + 3];
		}

		//To the next available one
		index += (3 + n);
	}
	
	cout << "pickes = ";
	for (int i = 0; i < 9; i++) {
		if(pickedName[i] != -1)
			cout << pickedName[i] << ", ";
	}
	cout << endl;

	return 1;
}

int selectObjects(GLFWwindow* window)
{
	//Width and height of picking region in window coordinates
	double delX = (pickedPoint[0][0] < pickedPoint[1][0]) ? (pickedPoint[1][0] - pickedPoint[0][0]) : (pickedPoint[0][0] - pickedPoint[1][0]);
	double delY = (pickedPoint[0][1] < pickedPoint[1][1]) ? (pickedPoint[1][1] - pickedPoint[0][1]) : (pickedPoint[0][1] - pickedPoint[1][1]);

	double x = (pickedPoint[0][0] + pickedPoint[1][0]) / 2;
	double y = (pickedPoint[0][1] + pickedPoint[1][1]) / 2;

	//Maximum 64 selections
	GLuint selectBuffer[64];
	glSelectBuffer(64, selectBuffer);

	//Current viewport
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	//Backup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();

	//Creates a projection matrix that can be used to restrict drawing to
	//a small region of the viewport
	gluPickMatrix(x, viewport[3] - y, delX, delY, viewport);	//y screen to viewport

	//Exploit the projection matrix for normal rendering
	setupProjectionMatrix();

	//Enter selection mode
	glRenderMode(GL_SELECT);

	//Render the objects for selection
	render(window);

	//Return to normal rendering mode and getting the picked object
	GLint hits = glRenderMode(GL_RENDER);
	findHits(hits, selectBuffer);

	//Restore the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	return 1;
}


void decideRectangle(float x1, float y1, float x2, float y2)
{
	if ((x1 <= x2 && y1 <= y2) || (x1 >= x2 && y1 >= y2)) {
		rectanglePoint[1][0] = x1;	rectanglePoint[1][1] = y2;
		rectanglePoint[3][0] = x2;	rectanglePoint[3][1] = y1;
	}
	else if ((x1 <= x2 && y1 >= y2) || (x1 >= x2 && y1 <= y2)) {
		rectanglePoint[1][0] = x2;	rectanglePoint[1][1] = y1;
		rectanglePoint[3][0] = x1;	rectanglePoint[3][1] = y2;
	}
}

void screen2world(float xs, float ys, float& xw, float& yw) {
	//In the world space, See reshape() in glSetup.cpp
	float aspect = (float)screenW / screenH;
	xw = 2.0f * (xs / (screenW - 1) - 0.5f) * aspect;
	yw = -2.0f * (ys / (screenH - 1) - 0.5f);
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	//Mouse cursor position in the screen coordinate system
	double xs, ys;
	glfwGetCursorPos(window, &xs, &ys);

	//Screen coordinate 2 world coordinate conversion
	float xw, yw;
	screen2world((float)xs, (float)ys, xw, yw);

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		inputMode = InputMode::DRAGGING; //Dragging starts

		rectanglePoint[0][0] = xw;   rectanglePoint[0][1] = yw; //Start point
		rectanglePoint[2][0] = xw;   rectanglePoint[2][1] = yw; //End point	

		decideRectangle(rectanglePoint[0][0], rectanglePoint[0][1], rectanglePoint[2][0], rectanglePoint[2][1]);

		pickedPoint[0][0] = xs;		pickedPoint[0][1] = ys;
		//cout << xs << ", " << ys << endl;
	}

	//The left button of the mouse is released
	if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
		inputMode = InputMode::COMPLETE; //Dragging ends

		rectanglePoint[2][0] = xw;	rectanglePoint[2][1] = yw;
		decideRectangle(rectanglePoint[0][0], rectanglePoint[0][1], rectanglePoint[2][0], rectanglePoint[2][1]);

		pickedPoint[1][0] = xs;		pickedPoint[1][1] = ys;
		
		//Retrieve the selected object
		selectObjects(window);
	}
}

void mouseMove(GLFWwindow* window, double x, double y) {
	//Update the end point whlie dragging
	if (inputMode == InputMode::DRAGGING) {
		screen2world((float)x, (float)y, rectanglePoint[2][0], rectanglePoint[2][1]);
		decideRectangle(rectanglePoint[0][0], rectanglePoint[0][1], rectanglePoint[2][0], rectanglePoint[2][1]);
	}
}