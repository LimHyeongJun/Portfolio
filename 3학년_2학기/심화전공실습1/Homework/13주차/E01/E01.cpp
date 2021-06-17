#include <GL/glew.h>				//OpenGL Extension Wrangler Library
#include "glSetup.h"

#include <glm/glm.hpp>				//OpenGL Mathematics
#include <glm/gtc/type_ptr.hpp>		//value_ptr()
using namespace glm;

#include <iostream>
#include <fstream>
using namespace std;

void init();
void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);

//Camera configuration
vec3	eye1(0, 0, 3);		//Eye position for the square example
vec3	at1(0, 0, 0);
vec3	eye5(3.5, 3, 3.5);	//Eye position for the cube example
vec3	at5(0, 0, 0);
vec3	eye6(0, 5, 15);		//Eye position for the floor example
vec3	at6(0, 0, 0);
vec3	upD(0, 1, 0);		//Exact up
vec3	forwardD;

//Light configuration
vec4	light1(0.0, 0.0, 1.0, 0);	//Light position for the square example
vec4	light5(1.0, 1.0, 1.0, 0);	//Light position for the cube example
vec4	light6(0, 5, 15, 0);		//Light position for the floor example

//Global coordinate frame
bool axes = true;
float AXIS_LENGTH = 2;
float AXIS_LINE_WIDTH = 2;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//Play configuration
bool	pause = true;

float timeStep = 1.0f / 120;	//120fps
float period = 4.0;

int frame = 0;

// Texture Wrapping
// 1 for original
// 2 for s to CLAMP,  t to CLAMP
// 3 for s to CLAMP,  t to REPEAT
// 4 for s to REPEAT, t to CLAMP
// 5 for s to REPEAT, t to REPEAT
int wrapping = 1;

//Textured square, upside down
bool	upsideDown = true;

//Size of the floor for the mipmapping example
float floorSize = 400;

//OpenGL texture unit
GLuint texID[5];

//Texture parameters
bool texture = true;	//Texture on/off
float textureNumRepeats = 1;

//MSAA
bool aaEnabled = false;

int main(int argc, char* argv[]) {
	//Setup far plane to move back for mipmapping test
	farDist = 200.0;

	//vsync should be 0 for precise time stepping.
	vsync = 0;

	//Initialize the OpenGL system
	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL) return -1;

	//GLEW: Supported version can be verified in glew.sourceforge.net/basic.html
	cerr << "Status: GLEW " << glewGetString(GLEW_VERSION) << endl;

	//Initializing GLEW for glGenerateMipmap()
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		cerr << "ERROR: " << glewGetErrorString(error) << endl;
		return 0;
	}

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

	float previous = (float)glfwGetTime();
	float elapsed = 0;
	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();			//Events

		//Time passed during a single loop
		float now = (float)glfwGetTime();
		float delta = now - previous;
		previous = now;

		//Time passed after the previous frame
		elapsed += delta;

		//Deal with the current frame
		if (elapsed > timeStep) {
			//Animate 1 frame
			if (!pause) frame += 1;

			elapsed = 0;		//Reset the elapsed time
		}

		render(window);				//Draw one frame
		glfwSwapBuffers(window);	//Swap buffers
	}

	//Terminate the glfw system
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void textureWrapping(int num)
{
	if (num == 0) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else if (num == 1) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else if (num == 2) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (num == 3) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else if (num == 4) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

bool loadRawTexture(const char* filename, int w, int h, int n, int num)
{
	//Open the raw texture file
	ifstream is(filename, ios::binary);
	if (is.fail()) {
		cout << "Can't open " << filename << endl;
		return false;
	}

	//Allocate memory
	GLubyte* raw = new GLubyte[w * h * n];

	//Read all the texels
	is.read((char*)raw, w * h * n);
	if (!is)		cout << "Error: only " << is.gcount() << "bytes could be read!" << endl;

	//Only 3 and 1
	if (n == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, raw);
	}
	else if (n == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0,
			GL_LUMINANCE, GL_UNSIGNED_BYTE, raw);
	}
	else {
		//Not supporting 2 channels
	}

	textureWrapping(num);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Deallocate memory
	delete[] raw;

	return true;
}

void computeMovementDirections()
{
	vec3	rightD;

	//Forward and backward direction for navigation
	forwardD = normalize(at6 - eye6);			//Gaze direction
	rightD = normalize(cross(forwardD, upD));
	forwardD = normalize(cross(upD, rightD));	//Forward direction to move
}

void init()
{
	//Forward and backward direction for navigation
	computeMovementDirections();

	//Generate 4 textures and bind appropriate images
	glGenTextures(5, texID);

	int indexNum = 0;

	//Raw texture
	for (int i = 0; i < 5; i++) {
		glBindTexture(GL_TEXTURE_2D, texID[i]);		//Marble
		loadRawTexture("m02_marble.raw", 512, 512, 3, i);
	}

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << "Keyboard Input: x for axes on/off" << endl;
	cout << "Keyboard Input: a for MSAA on/off" << endl;
	cout << "Keyboard Input: t for texture on/off" << endl;
	cout << "Keyboard Input: u for upside down on/off" << endl;
	cout << endl;
	cout << "Keyboard Input: 1 for original marble" << endl;
	cout << "Keyboard Input: 2 for s to CLAMP,  t to CLAMP" << endl;
	cout << "Keyboard Input: 3 for s to CLAMP,  t to REPEAT" << endl;
	cout << "Keyboard Input: 4 for s to REPEAT, t to CLAMP" << endl;
	cout << "Keyboard Input: 5 for s to REPEAT, t to REPEAT" << endl;
	cout << "Keyboard Input: SHIFT + up, down for inc/decreasing # repeats" << endl;
}


//Light
void setupLight(const vec4& light)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(light));
}

//Material
void setupMaterial()
{
	//Make it possible to change a subset of material parameters
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess = 25;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void drawTexturedSquare(float m = 1)
{
	//Square
	glBegin(GL_QUADS);

	//Objects's color affects the texture because default color blending is GL_MODULATE.
	//That is, glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(1, 1, 1);
	glNormal3f(0, 0, 1);

	//Upside down
	if (upsideDown) {
		glTexCoord2f(0, m - 0);		glVertex3f(0, 0, 0);
		glTexCoord2f(m, m - 0);		glVertex3f(1, 0, 0);
		glTexCoord2f(m, m - m);		glVertex3f(1, 1, 0);
		glTexCoord2f(0, m - m);		glVertex3f(0, 1, 0);
	}
	else {
		glTexCoord2f(0, 0);		glVertex3f(0, 0, 0);
		glTexCoord2f(m, 0);		glVertex3f(1, 0, 0);
		glTexCoord2f(m, m);		glVertex3f(1, 1, 0);
		glTexCoord2f(0, m);		glVertex3f(0, 1, 0);
	}
	glEnd();
}

void render(GLFWwindow* window)
{
	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Eye
	vec3	eye(0.0);
	vec3	at(0.0);
	eye = eye1; at = at1;		//Logo

	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], upD[0], upD[1], upD[2]);

	//MSAA
	if (aaEnabled)	glEnable(GL_MULTISAMPLE);
	else            glDisable(GL_MULTISAMPLE);

	//Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH*dpiScaling);
	}

	//Lighting
	//
	setupLight(light1);

	//Material
	setupMaterial();

	//Texture on/off
	if (texture)		glEnable(GL_TEXTURE_2D);
	else                glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texID[wrapping - 1]);	//Marble texture
	drawTexturedSquare(textureNumRepeats); 
		
}

void keyboard(GLFWwindow* window, int key, int scanmode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key)
		{
			//Quit
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

			//Play on/off
		case GLFW_KEY_SPACE:	pause = !pause; break;

			//Axes on/off
		case GLFW_KEY_X:		axes = !axes;	break;

			//Turn texture coordinates upside down
		case GLFW_KEY_U:		upsideDown = !upsideDown;	break;

			//Texture on/off
		case GLFW_KEY_T:		texture = !texture;			break;

			//MSAA on/off
		case GLFW_KEY_A:		aaEnabled = !aaEnabled;		break;

			//Texture Wrapping
		case GLFW_KEY_1:		wrapping = 1;	textureNumRepeats = 1;		break;
		case GLFW_KEY_2:		wrapping = 2;	textureNumRepeats = 2;		break;
		case GLFW_KEY_3:		wrapping = 3;	textureNumRepeats = 2;		break;
		case GLFW_KEY_4:		wrapping = 4;	textureNumRepeats = 2;		break;
		case GLFW_KEY_5:		wrapping = 5;	textureNumRepeats = 2;		break;
		}
	}

	//With the shift key
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (mods & GLFW_MOD_SHIFT))
	{
		switch (key)
		{
			//Texture number of repeats
		case GLFW_KEY_UP:		textureNumRepeats += 1;	break;
		case GLFW_KEY_DOWN:		textureNumRepeats -= 1;	break;
		}
	}
}