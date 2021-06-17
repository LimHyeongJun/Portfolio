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
vec3 eyeTopView(0, 10, 0);		//Top view
vec3 upTopView(0, 0, -1);		//Top view

vec3 eyeFrontView(0, 0, 10);	//Front view
vec3 upFrontView(0, 1, 0);		//Front view

vec3 eyeBirdView(0, -10, 4);	//Bird-eye view
vec3 upBirdView(0, 1, 0);		//Bird-eye view
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
int		view = 1;			//Top, front, bird-eye veiw

bool	rotationObject = false;	//Rotate the models
bool	rotationLight = false;	//Rotate the lights

float	thetaModel = 0;			//Rotation angle around the y-axis
float	thetaLight[3];

bool	lightOn[3];				//Point = 0, distant = 1, spot = 2 lights
bool	attenuation = false;	//Attenuation for point light

//Paly configuration
bool pause = true;

float timeStep = 1.0f / 120; //120fps
float period = 4.0f;

//Current frame
int frame = 0;

void reinitialize()
{
	frame = 0;

	lightOn[0] = true;	//Turn on only the point light
	lightOn[1] = false;
	lightOn[2] = false;

	thetaModel = 0;
	for (int i = 0; i < 3; i++)
		thetaLight[i] = 0;
}

void animate()
{
	frame += 1;

	//Rotation angle of the light
	if (rotationLight) {
		for (int i = 0; i < 3; i++)
			if (lightOn[i]) thetaLight[i] += 4 / period;	//degree
	}

	//Rotate angle the models
	if (rotationObject) thetaModel += 4 / period;	//degree
}

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
			if (!pause)	animate();

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
	//Animation system
	reinitialize();

	//Prepare quadric shapes
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricTexture(sphere, GL_FALSE);

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << "Keyboard Input: i for reinitialization" << endl;
	cout << "Keyboard Input: up for increasing period" << endl;
	cout << "Keyboard Input: down for decreasing period" << endl;
	cout << "Keyboard Input: v for the top, front, bird-eye view" << endl;
	cout << endl;
	cout << "Keyboard Input: p for a point light" << endl;
	cout << "Keyboard Input: a for light attenuation" << endl;
	cout << "Keyboard Input: l for rotation of lights" << endl;
	cout << "Keyboard Input: o for rotation of objects" << endl;
	cout << "Keyboard Input: ¡æ for adjust for the shininess coefficient of a point light larger" << endl;
	cout << "Keyboard Input: ¡ç for adjust for the shininess coefficient of a point light narrower" << endl;
}

void quit()
{
	//Delete quadric shapes
	gluDeleteQuadric(sphere);
}

GLfloat shininess = 0.0f;

void setupWhiteShinyMaterial()
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
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
void computeRotation(const vec3& a, const vec3& b, float& theta, vec3& axis)
{
	axis = cross(a, b);
	float	sinTheta = length(axis);
	float	cosTheta = dot(a, b);
	theta = float(atan2(sinTheta, cosTheta) * 180.0 / M_PI);
}

//Light
void setupLight(const vec4& p, int i)
{
	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0 + i, GL_POSITION, value_ptr(p));

	//Attenuation for the point and spot light
	if ((i == 0 || i == 2) && attenuation)
	{
		glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 1.0f);
		glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.1f);
		glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.05f);
	}
	else {		//Defalut value
		glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 1.0f);
		glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.0f);
		glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.0f);
	}

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);	//uniform light distribution
}

void drawArrow(const vec3& p)
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
	switch (view)
	{
	case 0: eye = eyeTopView;		up = upTopView;		break;
	case 1: eye = eyeFrontView;		up = upFrontView;	break;
	case 2: eye = eyeBirdView;		up = upBirdView;	break;
	}
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
	for (int i = 0; i < 3; i++)
	{
		//Just turn off the i-th light, if not lit
		if (!lightOn[i]) { glDisable(GL_LIGHT0 + i); continue; }

		//Turn on the i-th light
		glEnable(GL_LIGHT0 + i);

		//Dealing with the distant light
		lightP[i] = lightInitialP;
		if (i == 1) lightP[i].w = 0;

		//Lights rotate around the center of the world coordinate system
		mat4	R = rotate(mat4(1.0), radians(thetaLight[i]), axis);;
		lightP[i] = R * lightP[i];

		//Set up the i-th light
		setupLight(lightP[i], i);
	}

	//Draw the geometries of the lights
	drawArrow(lightP[0]);

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

		for (int j = 0; j < 3; j++)
		{
			glPushMatrix();

			glTranslatef(v[j].x, v[j].y, v[j].z);
			glRotatef(thetaModel, axis.x, axis.y, axis.z);

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

			//Axes
		case GLFW_KEY_X:		axes = !axes; break;

			//Initialization
		case GLFW_KEY_I: reinitialize(); break;

			//play on/off
		case GLFW_KEY_SPACE:	pause = !pause; break;

			//Period control
		case GLFW_KEY_UP:	period += 0.1f; break;
		case GLFW_KEY_DOWN: period = (float)max(period - 0.1, 0.1); break;

			//Top, front, bird-eye view
		case GLFW_KEY_V: view = (view + 1) % 3; break;

			//Turn on/off the point, distant, spot light
		case GLFW_KEY_P: lightOn[0] = !lightOn[0];	break;

			//Light attenuation
		case GLFW_KEY_A: attenuation = !attenuation; break;

			//Light: point, direction, spot
		case GLFW_KEY_L: rotationLight = !rotationLight; break;

			//Rotation: light position/direction, models
		case GLFW_KEY_O: rotationObject = !rotationObject; break;

		case GLFW_KEY_RIGHT: 
			if (shininess >= 0 && shininess < 10)
				shininess += 2;
			else
				shininess *= 2;
			break;
		case GLFW_KEY_LEFT: 
			if (shininess > 0 && shininess <= 10)
				shininess -= 2;
			else if (shininess == 0)
				break;
			else
				shininess /= 2;
			break;	
		}
	}
}