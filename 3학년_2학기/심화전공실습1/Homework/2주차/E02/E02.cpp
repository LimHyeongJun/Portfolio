#include "glSetup.h"
#include <iostream>

void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);

GLfloat bgColor[4] = { 1, 1, 1, 1 };

using namespace std;

GLenum mode = GL_POINTS;
bool filll = true;

int main(int argc, char* argv[]) {
	perspectiveView = false;

	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL)
		return -1;

	glfwSetKeyCallback(window, keyboard);

	reshape(window, windowW, windowH);

	cout << endl;
	cout << "Keyboard Input: f for polygon filling on/off" << endl;

	while (!glfwWindowShouldClose(window)) {
		render(window); //Draw one frame
		glfwSwapBuffers(window); //Swap buffers
		glfwPollEvents(); //Events
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void render(GLFWwindow* window) {
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (filll) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPointSize(5 * dpiScaling);

	glLineWidth(5 * dpiScaling);

	glBegin(GL_QUAD_STRIP);
	{
		glColor3f(1, 0, 0); glVertex2f(-1.2, 0.5);
		glColor3f(0, 1, 0); glVertex2f(-1.2, -0.5);
		glColor3f(0, 0, 0); glVertex2f(-0.4, 0.5);
		glColor3f(0, 0, 1); glVertex2f(-0.4, -0.5);		
		glColor3f(1, 0, 0); glVertex2f(0.4, 0.5);
		glColor3f(0, 1, 0); glVertex2f(0.4, -0.5);
		glColor3f(0, 0, 0); glVertex2f(1.2, 0.5);
		glColor3f(0, 0, 1); glVertex2f(1.2, -0.5);

		/*glColor3f(1, 0, 0); glVertex2f(-1.2, 0.5);
		glColor3f(0, 1, 0); glVertex2f(-1.2, -0.5);
		glColor3f(0, 0, 1); glVertex2f(-0.4, -0.5);
		glColor3f(0, 0, 0); glVertex2f(-0.4, 0.5);
		glColor3f(1, 0, 0); glVertex2f(0.4, 0.5);
		glColor3f(0, 1, 0); glVertex2f(0.4, -0.5);
		glColor3f(0, 0, 1); glVertex2f(1.2, -0.5);
		glColor3f(0, 0, 0); glVertex2f(1.2, 0.5);*/
	}
	glEnd();
}

void keyboard(GLFWwindow* window, int key, int scandmode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;

		case GLFW_KEY_F: filll = !filll; break;

		case GLFW_KEY_SPACE: break;
		case GLFW_KEY_PERIOD: break;
		case GLFW_KEY_LEFT: break;
		case GLFW_KEY_RIGHT: break;
		case GLFW_KEY_LEFT_BRACKET: break;
		case GLFW_KEY_RIGHT_BRACKET: break;
		case GLFW_KEY_UP: break;
		case GLFW_KEY_DOWN: break;
		}
	}
}