#include "glSetup.h"
#include <iostream>

void render(GLFWwindow* window);
void keyboard(GLFWwindow* window, int key, int code, int action, int mods);

GLfloat bgColor[4] = { 1, 1, 1, 1 };

using namespace std;

int main(int argc, char* argv[]) {
	perspectiveView = false;

	GLFWwindow* window = initializeOpenGL(argc, argv, bgColor);
	if (window == NULL)
		return -1;

	glfwSetKeyCallback(window, keyboard);

	reshape(window, windowW, windowH);

	cout << endl;
	cout << "Keyboard Input: q for quit" << endl;

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

	glLineWidth(5 * dpiScaling);

	glBegin(GL_LINES);
	{
		//Under line
		glColor3f(1, 0, 0); glVertex2f(-0.5, -0.5);
		glColor3f(0, 1, 0); glVertex2f(0.5, -0.5);

		//Right line
		glColor3f(0, 1, 0); glVertex2f(0.5, -0.5);
		glColor3f(0, 0, 1); glVertex2f(0.5, 0.5);

		//Top line
		glColor3f(0, 0, 1); glVertex2f(0.5, 0.5);
		glColor3f(0, 0, 0); glVertex2f(-0.5, 0.5);

		//Left line
		glColor3f(0, 0, 0); glVertex2f(-0.5, 0.5);
		glColor3f(1, 0, 0); glVertex2f(-0.5, -0.5);
	}
	glEnd();
}

void keyboard(GLFWwindow* window, int key, int scandmode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;
		}
	}
}