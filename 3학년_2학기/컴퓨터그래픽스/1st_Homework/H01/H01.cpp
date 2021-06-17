#include "glSetup.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES		//To include the definition of M_PI in math.h
#endif

#include <glm/glm.hpp>				//OpenGL Mathematics
#include <glm/gtx/string_cast.hpp>	//glm::to_string()
#include <glm/gtc/type_ptr.hpp>		//glm::value_ptr()
using namespace glm;

#include <iostream>
using namespace std;

void init();
void quit();
void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);

//Camera configuration
vec3 eye(3.5, 3, 3.5);
vec3 center(0, 0, 0);
vec3 up(0, 1, 0);

//Light configuration
vec4 light(5.0, 5.0, 5.0, 1);		//Light position

//Global coordinate frame
float AXIS_LENGTH = 3;
float AXIS_LINE_WIDTH = 2;

int MAX_I = 36;
int MAX_J = 18;

int direction = 0;

//Colors
GLfloat bgColor[4] = { 1, 1, 1, 1 };

//Selected example
int selection = 1;

//Paly configuration
bool pause = false;

float timeStep = 1.0f / 120; //120fps
float period = 4.0;

//Current frame
int frame = 0;

int main(int argc, char* argv[]) {
	//FPS control: vsync should be 0 for precise time stepping
	vsync = 0;	//0 for immediate mode(Tearing possible)

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
			//Rotate the line segment if not paused
			if (!pause) frame += 1;

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

glm::vec3* p[36] = { NULL };
glm::vec3* fnormal[36] = { NULL };
glm::vec3* centerPoint[36] = { NULL };
glm::vec3* v[36] = { NULL };

void init()
{
	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << endl;
	cout << "Keyboard Input: 1 for Draw the wireframe only" << endl;
	cout << "Keyboard Input: 2 for Draw the quads and the wireframe" << endl;
	cout << "Keyboard Input: 3 for Sweep angle control around the y-axis" << endl;
	cout << "Keyboard Input: 4 for Two-sided constant shading" << endl;

	for (int i = 0; i < MAX_I; i++) {
		p[i] = new vec3[MAX_J];
		fnormal[i] = new vec3[MAX_J];
		centerPoint[i] = new vec3[MAX_J];
		v[i] = new vec3[MAX_J];
	}

	//초기값
	p[0][0] = { 1.3, 1, 0 };
	glm::vec4 torusOutsidePoint = { 1.3, 1, 0, 1 };
	glm::vec4 firstCirclePoint = { 1.3, 1, 0, 1 };

	glm::vec3 zaxis(0, 0, 1);
	glm::vec3 yaxis(0, 1, 0);
	vec3 pivot = { 1, 1, 0 };

	glm::mat4 A(1.0);

	//torus의 맨 바깥쪽 점들
	for (int i = 1; i < MAX_I; i++) {
		A = glm::mat4(1.0);
		A = glm::rotate(A, glm::radians(10.0f), yaxis);  //Radians

		torusOutsidePoint = A * torusOutsidePoint;

		p[i][0] = { torusOutsidePoint.x, torusOutsidePoint.y, torusOutsidePoint.z };
		torusOutsidePoint = { p[i][0].x, p[i][0].y, p[i][0].z, 1 };
	}

	//first circle
	for (int j = 1; j < MAX_J; j++) {
		A = glm::mat4(1.0);
		A = glm::translate(A, pivot);
		A = glm::rotate(A, glm::radians(20.0f), zaxis);
		A = glm::translate(A, -pivot);

		firstCirclePoint = A * firstCirclePoint;

		p[0][j] = { firstCirclePoint.x, firstCirclePoint.y, firstCirclePoint.z };

		firstCirclePoint = { p[0][j].x, p[0][j].y, p[0][j].z, 1 };
	}

	//Calculate all point
	for (int j = 1; j < MAX_J; j++) {
		vec4 temp = { p[0][j].x, p[0][j].y, p[0][j].z, 1 };
		for (int i = 1; i < MAX_I; i++) {
			A = glm::mat4(1.0);
			A = glm::rotate(A, glm::radians(10.0f), yaxis);

			temp = A * temp;

			p[i][j] = { temp.x, temp.y, temp.z };
		}
	}

	//calculate faces normal vector
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			vec3 a = p[(i + 1) % MAX_I][j] - p[i][j];
			vec3 b = p[i][(j + 1) % MAX_J] - p[i][j];
			vec3 result = glm::cross(a, b);
			normalize(result);

			fnormal[i][j] = result;
		}
	}

	//calculate all faces center point
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			vec3 sum = p[i][j] + p[(i + 1) % MAX_I][j] +
				p[(i + 1) % MAX_I][(j + 1) % MAX_J] + p[i][(j + 1) % MAX_J];

			centerPoint[i][j] = { (sum.x) / 4.0f, (sum.y) / 4.0f, (sum.z) / 4.0f };
			v[i][j] = eye - centerPoint[i][j];
		}
	}
}

void quit()
{
	for (int i = 0; i < MAX_I; i++) {
		if (p[i]) { delete[] p[i]; p[i] = NULL; }
		if (fnormal[i]) { delete[] fnormal[i]; fnormal[i] = NULL; }
		if (centerPoint[i]) { delete[] centerPoint[i]; centerPoint[i] = NULL; }
		if (v[i]) { delete[] v[i]; v[i] = NULL; }
	}
}

//Light
void setupLight()
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
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess = 128;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setDiffuseColor(const vec3& color)
{
	GLfloat mat_diffuse[4] = { color[0],color[1], color[2], 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
}

void part1()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	setDiffuseColor(glm::vec3(0, 0, 0));	//Material
	glBegin(GL_QUADS);
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			glNormal3fv(value_ptr(fnormal[i][j]));
			glVertex3fv(value_ptr(p[i][j]));
			glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
		}
	}
	glEnd();
}

void part2()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	setDiffuseColor(glm::vec3(0, 0, 0));	//Material
	glBegin(GL_QUADS);
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			glNormal3fv(value_ptr(fnormal[i][j]));
			glVertex3fv(value_ptr(p[i][j]));
			glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
		}
	}
	glEnd();

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonOffset(1.0f, 1.0f);
	setDiffuseColor(glm::vec3(0, 0, 1));	//Material
	glBegin(GL_QUADS);
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			glNormal3fv(value_ptr(fnormal[i][j]));
			glVertex3fv(value_ptr(p[i][j]));
			glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
		}
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void part3()
{
	if (direction == 0)
	{
		setDiffuseColor(glm::vec3(0, 0, 0));	//Material
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < MAX_J; j++) {
			glVertex3fv(value_ptr(p[0][j]));
		}
		glEnd();
	}
	else if (direction > 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		setDiffuseColor(glm::vec3(0, 0, 0));	//Material
		glBegin(GL_QUADS);
		for (int i = 0; i < direction; i++) {
			for (int j = 0; j < MAX_J; j++) {
				glNormal3fv(value_ptr(fnormal[i][j]));
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
			}
		}
		glEnd();

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		setDiffuseColor(glm::vec3(0, 0, 1));	//Material
		glPolygonOffset(1.0f, 1.0f);
		glBegin(GL_QUADS);
		for (int i = 0; i < direction; i++) {
			for (int j = 0; j < MAX_J; j++) {
				glNormal3fv(value_ptr(fnormal[i][j]));
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else if (direction < 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		setDiffuseColor(glm::vec3(0, 0, 0));	//Material
		glBegin(GL_QUADS);
		for (int i = MAX_I + direction; i < MAX_I; i++) {
			for (int j = 0; j < MAX_J; j++) {
				glNormal3fv(value_ptr(fnormal[i][j]));
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
			}
		}
		glEnd();

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		setDiffuseColor(glm::vec3(0, 0, 1));	//Material
		glPolygonOffset(1.0f, 1.0f);
		glBegin(GL_QUADS);
		for (int i = MAX_I + direction; i < MAX_I; i++) {
			for (int j = 0; j < MAX_J; j++) {
				glNormal3fv(value_ptr(fnormal[i][j]));
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}

void part4()
{
	if (direction == 0)
	{
		//setDiffuseColor(glm::vec3(0, 0, 0));	//Material
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < MAX_J; j++) {
			glVertex3fv(value_ptr(p[0][j]));
		}
		glEnd();
	}
	else if (direction > 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		setDiffuseColor(glm::vec3(0, 0, 0));	//Material
		//glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		for (int i = 0; i < direction; i++) {
			for (int j = 0; j < MAX_J; j++) {
				glNormal3fv(value_ptr(fnormal[i][j]));
				/*glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));*/
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			}
		}
		glEnd();

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glBegin(GL_QUADS);
		for (int i = 0; i < direction; i++) {
			for (int j = 0; j < MAX_J; j++) {
				if (dot(fnormal[i][j], v[i][j]) > 0) {
					setDiffuseColor(glm::vec3(0, 0, 1));	//Material
					//glColor3f(0, 0, 1);
					glNormal3fv(value_ptr(fnormal[i][j]));
				}
				else {
					setDiffuseColor(glm::vec3(1, 0, 0));
					//glColor3f(1, 0, 0);
					glNormal3fv(value_ptr(-fnormal[i][j]));
				}
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else if (direction < 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//setDiffuseColor(glm::vec3(0, 0, 0));	//Material
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		for (int i = MAX_I + direction; i < MAX_I; i++) {
			for (int j = 0; j < MAX_J; j++) {
				glNormal3fv(value_ptr(fnormal[i][j]));
				/*glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));*/
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			}
		}
		glEnd();

		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glBegin(GL_QUADS);
		for (int i = MAX_I + direction; i < MAX_I; i++) {
			for (int j = 0; j < MAX_J; j++) {
				if (dot(fnormal[i][j], v[i][j]) > 0) {
					//setDiffuseColor(glm::vec3(0, 0, 1));	//Material
					glColor3f(0, 0, 1);
					glNormal3fv(value_ptr(fnormal[i][j]));
				}
				else {
					//setDiffuseColor(glm::vec3(1, 0, 0));
					glColor3f(1, 0, 0);
					glNormal3fv(value_ptr(-fnormal[i][j]));
				}
				/*glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));*/
				glVertex3fv(value_ptr(p[i][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
				glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
				glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}

void render(GLFWwindow* window)
{
	//Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	glDisable(GL_LIGHTING);
	drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH*dpiScaling);

	//Lighting
	setupLight();

	//Material
	setupMaterial();

	switch (selection)
	{
	case 1: part1();			break;
	case 2: part2();			break;
	case 3: part3();			break;
	case 4: part4();			break;
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

			//Play on/off
		case GLFW_KEY_SPACE: pause = !pause; break;

			//Example selection
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;
		case GLFW_KEY_3: selection = 3; break;
		case GLFW_KEY_4: selection = 4; break;

		case GLFW_KEY_RIGHT: direction < MAX_I ? direction++ : direction = direction;		break;
		case GLFW_KEY_LEFT: direction > -MAX_I ? direction-- : direction = direction;		break;
		}
	}
}