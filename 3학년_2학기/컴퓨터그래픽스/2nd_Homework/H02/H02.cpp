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

//Camera configuration
vec3 eyeTopView(0, 5, 0);		//Top view
vec3 upTopView(0, 0, -1);		//Top view

vec3 eyeCenterView(3.5, 3, 3.5);
vec3 upCenterView(0, 1, 0);

//Light configuration
vec4 light(5.0, 5.0, 5.0, 1);		//Light position

//Light configuration
vec4 lightInitialP(0.0, 2.0, 0.0, 1);	//Initial light position

//Global coordinate frame
bool axes = true;

//Global coordinate frame
float AXIS_LENGTH = 3;
float AXIS_LINE_WIDTH = 2;

int MAX_I = 36;
int MAX_J = 18;

int direction = 0;

//Show nomral vectors
bool faceNormal = false;
bool vertexNormal = false;

//Show wire frame
bool wireframe = false;

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



int		view = 1;			//Top, center veiw

bool	rotationObject = false;	//Rotate the models
bool	rotationLight = false;	//Rotate the lights

float	thetaModel = 0;			//Rotation angle around the y-axis
float	thetaLight[3];

bool	lightOn[3];				//Point = 0, distant = 1, spot = 2 lights
bool	attenuation = false;	//Attenuation for point light

bool	exponent = false;
float	exponentInitial = 0.0;					//[0, 128]
float	exponentValue = exponentInitial;
float	exponentNorm = exponentValue / 128.0f;	//[0, 1]

bool	cutoff = false;
float	cutoffMax = 60;							//[0, 90] degree
float	cutoffInitial = 30.0;					//[0, cutoffMax] degree
float	cutoffValue = cutoffInitial;
float	cutoffNorm = cutoffValue / cutoffMax;	//[0, 1]

void reinitialize()
{
	frame = 0;

	lightOn[0] = true;	//Turn on only the point light
	lightOn[1] = false;
	lightOn[2] = false;

	thetaModel = 0;
	for (int i = 0; i < 3; i++)
		thetaLight[i] = 0;

	exponentValue = exponentInitial;
	exponentNorm = exponentValue / 128.0f;

	cutoffValue = cutoffInitial;
	cutoffNorm = cutoffValue / cutoffMax;
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

	//Periodicallly change the exponent and/or cutoff value of the spot light
	if (lightOn[2] && exponent) {
		exponentNorm += float(radians(4.0 / period) / M_PI);
		exponentValue = float(128.0f * (acos(cos(exponentNorm * M_PI)) / M_PI));
	}
	if (lightOn[2] && cutoff) {
		cutoffNorm += float(radians(4.0 / period) / M_PI);
		cutoffValue = float(cutoffMax * (acos(cos(exponentNorm * M_PI)) / M_PI));
	}
}

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
			//if (!pause) frame += 1;
			if (!pause) animate();

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
glm::vec3* vnormal[36] = { NULL };
glm::vec3* centerPoint[36] = { NULL };
glm::vec3* v[36] = { NULL };

//Sphere, cylinder
GLUquadricObj* sphere = NULL;
GLUquadricObj* cylinder = NULL;
GLUquadricObj* cone = NULL;

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

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricOrientation(cylinder, GLU_OUTSIDE);
	gluQuadricTexture(cylinder, GL_FALSE);

	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluQuadricNormals(cone, GLU_SMOOTH);
	gluQuadricOrientation(cone, GLU_OUTSIDE);
	gluQuadricTexture(cone, GL_FALSE);

	//Keyboard
	cout << endl;
	cout << "Keyboard Input: space for play/pause" << endl;
	cout << "Keyboard Input: f for show face normal vector" << endl;
	cout << "Keyboard Input: n for show face normal vector" << endl;
	cout << "Keyboard Input: i for reinitialization" << endl;
	cout << "Keyboard Input: up for increasing period" << endl;
	cout << "Keyboard Input: down for decreasing period" << endl;
	cout << "Keyboard Input: v for the top, center view" << endl;
	cout << "Keyboard Input: w for show wireframe(only two-sided lighting)" << endl;
	cout << endl;
	cout << "Keyboard Input: p for a point light" << endl;
	cout << "Keyboard Input: d for a distant light" << endl;
	cout << "Keyboard Input: s for a spot light" << endl;
	cout << "Keyboard Input: a for light attenuation" << endl;
	cout << "Keyboard Input: e for time dependent exponent of a spot light" << endl;
	cout << "Keyboard Input: c for time dependent cutoff of a spot light" << endl;
	cout << "Keyboard Input: m for predefined material parameters" << endl;
	cout << "Keyboard Input: l for rotation of lights" << endl;
	cout << "Keyboard Input: o for rotation of objects" << endl;
	cout << "Keyboard Input: 1 for Draw the quads and the wireframe" << endl;
	cout << "Keyboard Input: 2 for Sweep angle control around the y-axis to demostrate two-sided lighting" << endl;

	for (int i = 0; i < MAX_I; i++) {
		p[i] = new vec3[MAX_J];
		fnormal[i] = new vec3[MAX_J];
		vnormal[i] = new vec3[MAX_J];
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

			fnormal[i][j] *= 5.0f;
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

	//calculate all vertices normal vector
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			vnormal[i][j] += fnormal[i][j];
			vnormal[i][j] += fnormal[i][(j + MAX_J - 1) % MAX_J];
			vnormal[i][j] += fnormal[(i + MAX_I - 1) % MAX_I][j];
			vnormal[i][j] += fnormal[(i + MAX_I - 1) % MAX_I][(j + MAX_J - 1) % MAX_J];

			vnormal[i][j] = normalize(vnormal[i][j]);
			vnormal[i][j] *= 0.1f;
		}
	}
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

//Draw a cylinder using a GLU quadric
void drawCylinder(float radius, float height, int slices, int stacks)
{
	gluCylinder(cylinder, radius, radius, height, slices, stacks);
}

//Draw a cylinder using a GLU quadric
void drawCone(float radius, float height, int slices, int stacks)
{
	gluCylinder(cone, 0, radius, height, slices, stacks);
}

void quit()
{
	for (int i = 0; i < MAX_I; i++) {
		if (p[i]) { delete[] p[i]; p[i] = NULL; }
		if (fnormal[i]) { delete[] fnormal[i]; fnormal[i] = NULL; }
		if (centerPoint[i]) { delete[] centerPoint[i]; centerPoint[i] = NULL; }
		if (v[i]) { delete[] v[i]; v[i] = NULL; }
	}

	//Delete quadric shapes
	gluDeleteQuadric(sphere);
	gluDeleteQuadric(cylinder);
	gluDeleteQuadric(cone);

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

//Material
void setupColoredMaterial(const vec3& color)
{
	//Material
	GLfloat mat_ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse[4] = { color[0], color[1], color[2], 1.0f };
	GLfloat mat_specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess = 100;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
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

	if (i == 2)		//Spot light
	{
		vec3 spotDirection = -vec3(p);
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, value_ptr(spotDirection));
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, cutoffValue);		//[0, 90]
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, exponentValue);	//[0, 128]
	}
	else {		//Point and distant light.
		// 180 to turn off cutoff when it has been used as a spot light
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180);	//uniform light distribution
	}
}

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

	if (!tailOnly)
	{
		float	theta;
		vec3	axis;
		computeRotation(vec3(0, 0, 1), vec3(0, 0, 0) - vec3(p), theta, axis);
		glRotatef(theta, axis.x, axis.y, axis.z);
	}

	//Tail sphere
	float	arrowTailRadius = 0.05f;
	glColor3f(1, 0, 0);		//ambient and diffuse
	drawSphere(arrowTailRadius, 16, 16);

	if (!tailOnly)
	{
		//Shaft cylinder
		float	arrowShaftRadius = 0.02f;
		float	arrowShaftLength = 0.2f;
		glColor3f(0, 1, 0);
		drawCylinder(arrowShaftRadius, arrowShaftLength, 16, 5);

		//Head cone
		float	arrowheadHeight = 0.09f;
		float	arrowheadRadius = 0.06f;
		glTranslatef(0, 0, arrowShaftLength + arrowheadHeight);
		glRotatef(180, 1, 0, 0);
		glColor3f(0, 0, 1);	//ambient and diffuse
		drawCone(arrowheadRadius, arrowheadHeight, 16, 5);
	}

	glPopMatrix();

	//For convential material setting
	glDisable(GL_COLOR_MATERIAL);
}

void drawSpotLight(const vec3& p, float cutoff)
{
	glPushMatrix();

	glTranslatef(p.x, p.y, p.z);

	float	theta;
	vec3	axis;
	computeRotation(vec3(0, 0, 1), vec3(0, 0, 0) - vec3(p), theta, axis);
	glRotatef(theta, axis.x, axis.y, axis.z);

	//Color
	setupColoredMaterial(vec3(0, 0, 1));

	//tan(cutoff) = r/h
	float	h = 0.15f;
	float	r = h * tan(radians(cutoff));
	drawCone(r, h, 16, 5);

	//Color
	setupColoredMaterial(vec3(1, 0, 0));

	//Apex
	float	apexRadius = 0.06f * (0.5f + exponentValue / 128.0f);
	drawSphere(apexRadius, 16, 16);

	glPopMatrix();
}



void setDiffuseColor(const vec3& color)
{
	GLfloat mat_diffuse[4] = { color[0],color[1], color[2], 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
}

void showFaceNormal()
{
	vec3* endPoint[36] = { NULL };

	for (int i = 0; i < MAX_I; i++) {
		endPoint[i] = new vec3[MAX_J];
	}

	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			endPoint[i][j] = centerPoint[i][j] + fnormal[i][j];
		}
	}

	glBegin(GL_LINES);
	setDiffuseColor(glm::vec3(0, 1, 0));	//Material
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			glVertex3fv(value_ptr(centerPoint[i][j]));
			glVertex3fv(value_ptr(endPoint[i][j]));
		}
	}
	glEnd();
}

void showVertexNormal()
{
	vec3* endPoint[36] = { NULL };

	for (int i = 0; i < MAX_I; i++) {
		endPoint[i] = new vec3[MAX_J];
	}

	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			endPoint[i][j] = p[i][j] + vnormal[i][j];
		}
	}

	glBegin(GL_LINES);
	setDiffuseColor(glm::vec3(1, 0, 0));	//Material
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			glVertex3fv(value_ptr(p[i][j]));
			glVertex3fv(value_ptr(endPoint[i][j]));
		}
	}
	glEnd();
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
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
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
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
			glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
			glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
		}
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}


void part2()
{
	GLfloat mat_blue[4] = { 0, 0, 1, 1 };
	GLfloat mat_red[4] = { 1, 0, 0, 1 };

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
		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setDiffuseColor(glm::vec3(0, 0, 0));	//Material
			glBegin(GL_QUADS);
			for (int i = 0; i < direction; i++) {
				for (int j = 0; j < MAX_J; j++) {
					if (dot(fnormal[i][j], v[i][j]) > 0) {
						glNormal3fv(value_ptr(fnormal[i][j]));
					}
					else {
						glNormal3fv(value_ptr(-fnormal[i][j]));
					}
					glVertex3fv(value_ptr(p[i][j]));
					glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
					glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
					glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				}
			}
			glEnd();
		}

		glDisable(GL_CULL_FACE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glBegin(GL_QUADS);
		for (int i = 0; i < direction; i++) {
			for (int j = 0; j < MAX_J; j++) {
				if (dot(fnormal[i][j], v[i][j]) > 0) {
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue);
				}
				else {
					glMaterialfv(GL_BACK, GL_DIFFUSE, mat_red);
				}
				glNormal3fv(value_ptr(fnormal[i][j]));
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
		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setDiffuseColor(glm::vec3(0, 0, 0));	//Material
			glBegin(GL_QUADS);
			for (int i = MAX_I + direction; i < MAX_I; i++) {
				for (int j = 0; j < MAX_J; j++) {
					glNormal3fv(value_ptr(fnormal[i][j]));
					glVertex3fv(value_ptr(p[i][j]));
					glVertex3fv(value_ptr(p[(i + 1) % MAX_I][j]));
					glVertex3fv(value_ptr(p[(i + 1) % MAX_I][(j + 1) % MAX_J]));
					glVertex3fv(value_ptr(p[i][(j + 1) % MAX_J]));
				}
			}
			glEnd();
		}

		glDisable(GL_CULL_FACE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonOffset(1.0f, 1.0f);
		glBegin(GL_QUADS);
		for (int i = MAX_I + direction; i < MAX_I; i++) {
			for (int j = 0; j < MAX_J; j++) {
				if (dot(fnormal[i][j], v[i][j]) > 0) {
					glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue);
				}
				else {
					glMaterialfv(GL_BACK, GL_DIFFUSE, mat_red);
				}
				glNormal3fv(value_ptr(fnormal[i][j]));
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

	switch (view)
	{
	case 0: eye = eyeTopView;		up = upTopView;		break;
	case 1: eye = eyeCenterView;	up = upCenterView;	break;
	}
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	//Axes
	if (axes) {
		glDisable(GL_LIGHTING);
		drawAxes(AXIS_LENGTH, AXIS_LINE_WIDTH*dpiScaling);
	}

	//Rotation of the light or 3x3 models
	vec3 axis(1, 0, 1);
	axis = normalize(axis);

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
		mat4	R = rotate(mat4(1.0), radians(thetaLight[i]), axis);
		lightP[i] = R * lightP[i];

		//Set up the i-th light
		setupLight(lightP[i], i);
	}

	//Draw the geometries of the lights
	for (int i = 0; i < 3; i++)
	{
		if (!lightOn[i])		continue;

		if (i == 2)	drawSpotLight(lightP[i], cutoffValue);
		else
		{
			drawArrow(lightP[i], i == 0);	//Tail only for a point light
		}
	}

	//Material
	setupMaterial();

	switch (selection)
	{
	case 1: part1();			break;
	case 2: part2();			break;
	}

	if (faceNormal)
		showFaceNormal();

	if (vertexNormal)
		showVertexNormal();
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

			//Play on/off
		case GLFW_KEY_SPACE: pause = !pause; break;

			//Period control
		case GLFW_KEY_UP:	period += 0.1f; break;
		case GLFW_KEY_DOWN: period = (float)max(period - 0.1, 0.1); break;

			//Top, front, bird-eye view
		case GLFW_KEY_V: view = (view + 1) % 2; break;

			//Turn on/off the point, distant, spot light
		case GLFW_KEY_P: lightOn[0] = !lightOn[0];	break;
		case GLFW_KEY_D: lightOn[1] = !lightOn[1];	break;
		case GLFW_KEY_S: lightOn[2] = !lightOn[2];	break;

			//Light attenuation
		case GLFW_KEY_A: attenuation = !attenuation; break;

			//Light: point, direction, spot
		case GLFW_KEY_L: rotationLight = !rotationLight; break;

			//Rotation: light position/direction, models
		case GLFW_KEY_O: rotationObject = !rotationObject; break;

			//Time dependent exponent of a spot light
		case GLFW_KEY_E: exponent = !exponent; break;

			//Time dependent cutoff of a spot light
		case GLFW_KEY_C: cutoff = !cutoff; break;

			//Show face normal vector
		case GLFW_KEY_F: faceNormal = !faceNormal;	break;

			//Show vertex normal vector
		case GLFW_KEY_N: vertexNormal = !vertexNormal;	break;

			//Show vertex normal vector
		case GLFW_KEY_W: wireframe = !wireframe;	break;

			//Example selection
		case GLFW_KEY_1: selection = 1; break;
		case GLFW_KEY_2: selection = 2; break;

		case GLFW_KEY_RIGHT: direction < MAX_I ? direction++ : direction = direction;		break;
		case GLFW_KEY_LEFT: direction > -MAX_I ? direction-- : direction = direction;		break;
		}
	}
}