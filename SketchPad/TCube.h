#pragma once
#include "TGraphic.h"


class TCube : public TGraphic {
private:
	float size;
	float x, y, z;
	float r, g, b;
public:
	TCube(float size, float x, float y, float z, float r, float g, float b)
		: size(size), x(x), y(y), z(z), r(r), g(g), b(b) {}

	void DrawCube(float size, float x, float y, float z, float r, float g, float b)
	{
		float halfSize = size / 2.0f;

		GLfloat vertices[8][3] = {
	{ -halfSize, -halfSize, -halfSize },
	{  halfSize, -halfSize, -halfSize },
	{  halfSize,  halfSize, -halfSize },
	{ -halfSize,  halfSize, -halfSize },
	{ -halfSize, -halfSize,  halfSize },
	{  halfSize, -halfSize,  halfSize },
	{  halfSize,  halfSize,  halfSize },
	{ -halfSize,  halfSize,  halfSize }
		};

		glBegin(GL_QUADS);
		glColor3f(r, g, b);

		glVertex3f(vertices[0][0] + x, vertices[0][1] + y, vertices[0][2] + z);
		glVertex3f(vertices[1][0] + x, vertices[1][1] + y, vertices[1][2] + z);
		glVertex3f(vertices[2][0] + x, vertices[2][1] + y, vertices[2][2] + z);
		glVertex3f(vertices[3][0] + x, vertices[3][1] + y, vertices[3][2] + z);

		glVertex3f(vertices[4][0] + x, vertices[4][1] + y, vertices[4][2] + z);
		glVertex3f(vertices[5][0] + x, vertices[5][1] + y, vertices[5][2] + z);
		glVertex3f(vertices[6][0] + x, vertices[6][1] + y, vertices[6][2] + z);
		glVertex3f(vertices[7][0] + x, vertices[7][1] + y, vertices[7][2] + z);

		glVertex3f(vertices[0][0] + x, vertices[0][1] + y, vertices[0][2] + z);
		glVertex3f(vertices[4][0] + x, vertices[4][1] + y, vertices[4][2] + z);
		glVertex3f(vertices[7][0] + x, vertices[7][1] + y, vertices[7][2] + z);
		glVertex3f(vertices[3][0] + x, vertices[3][1] + y, vertices[3][2] + z);

		glVertex3f(vertices[1][0] + x, vertices[1][1] + y, vertices[1][2] + z);
		glVertex3f(vertices[5][0] + x, vertices[5][1] + y, vertices[5][2] + z);
		glVertex3f(vertices[6][0] + x, vertices[6][1] + y, vertices[6][2] + z);
		glVertex3f(vertices[2][0] + x, vertices[2][1] + y, vertices[2][2] + z);

		glVertex3f(vertices[3][0] + x, vertices[3][1] + y, vertices[3][2] + z);
		glVertex3f(vertices[2][0] + x, vertices[2][1] + y, vertices[2][2] + z);
		glVertex3f(vertices[6][0] + x, vertices[6][1] + y, vertices[6][2] + z);
		glVertex3f(vertices[7][0] + x, vertices[7][1] + y, vertices[7][2] + z);

		glVertex3f(vertices[0][0] + x, vertices[0][1] + y, vertices[0][2] + z);
		glVertex3f(vertices[1][0] + x, vertices[1][1] + y, vertices[1][2] + z);
		glVertex3f(vertices[5][0] + x, vertices[5][1] + y, vertices[5][2] + z);
		glVertex3f(vertices[4][0] + x, vertices[4][1] + y, vertices[4][2] + z);

		glEnd();
	}
	void Draw() override {
		DrawCube(size, x, y, z, r, g, b);
	}

};