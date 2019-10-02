#include <cstdio>

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
# define M_PI 3.14159265358979323846  /* pi */

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius);

int main(void)
{
	GLFWwindow *window;

	// ���������� �������� GLFW
	if (!glfwInit())
	{
		return -1;
	}

	// ��������� ����
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Laboratory 1 Variant 1", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//�����������
	float vertices[] =
	{
		500, 300, 0.0, // top right corner
		150, 300, 0.0, // top left corner
		150, 50, 0.0, // bottom left corner
		500, 50, 0.0 // bottom right corner
	};

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // 1 � 2 -������� �������� ����� �����, ������������� � �����
	glMatrixMode(GL_PROJECTION); // ����� ������� ��������  
	glLoadIdentity(); // ������������ �� ������� ��������� (0,0,0)
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix ������� �� ��'��� ���� �������
	glLoadIdentity(); 

	// ���� ���� ���������� �� ����� ����
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //- ������ ���� ������
		glClear(GL_COLOR_BUFFER_BIT); // �������� ���� (������ ����)

		// Render OpenGL here �����������
		glColor3f(0.3, 0.3, 0.3);
		glEnableClientState(GL_VERTEX_ARRAY); // ��� ����� �������������� ������
		glVertexPointer(3, GL_FLOAT, 0, vertices); // 1 - ��-��� ������� �����, ���, ����, �����)
		glDrawArrays(GL_QUADS, 0, 4); // �-� ��� ���������: 1 - �������, ���� ����� ����������, 2 - ���. ���. ������, 3 -��-��� ������
		glDisableClientState(GL_VERTEX_ARRAY); // ���� �����

		// render OpenGL here ����
		glColor3f(1.0, 0.0, 0.0);
		drawCircle(SCREEN_WIDTH / 2, 250, 0, 70);
				
		// ������ ������� � ����� ������ - ������� �����������
		//������� ����� ������ ����������� ����, ����� - ���������
		glfwSwapBuffers(window);

		// �������� �� ��䳿(���������� �����, ���������� ����)
		glfwPollEvents();
	}
	//������� �������
	glfwTerminate();

	return 0;
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
{
	const int numberOfSides = 100;
	const int numberOfVertices = numberOfSides + 2;

	GLfloat twicePi = 2.0f * M_PI;
	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[(numberOfVertices) * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}