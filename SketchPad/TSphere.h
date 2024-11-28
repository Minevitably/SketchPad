#pragma once
#include "TGraphic.h"

class TSphere : public TGraphic {
private:
    float radius;
    float x, y, z;
    float r, g, b; // ��ɫ

public:
	TSphere(float radius, float x, float y, float z, float r, float g, float b)
        : radius(radius), x(x), y(y), z(z), r(r), g(g), b(b) {}

	void DrawSphere(float radius, float x, float y, float z, float r, float g, float b)
	{
		const int slices = 20; // ������Ƭ��
		const int stacks = 20; // γ����Ƭ��

		glBegin(GL_TRIANGLES); // ʹ�������λ�������

		for (int i = 0; i < stacks; ++i) {
			float lat0 = M_PI * (-0.5 + (float)(i) / stacks); // ��ǰγ��
			float z0 = radius * sin(lat0); // z ����
			float zr0 = radius * cos(lat0); // �뾶

			float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks); // ��һ��γ��
			float z1 = radius * sin(lat1);
			float zr1 = radius * cos(lat1);

			for (int j = 0; j < slices; ++j) {
				float lng = 2 * M_PI * (float)(j) / slices; // ��ǰ����
				float x0 = zr0 * cos(lng); // x ����
				float y0 = zr0 * sin(lng); // y ����
				float x1 = zr1 * cos(lng); // ��һ��� x ����
				float y1 = zr1 * sin(lng); // ��һ��� y ����

				// ������ɫ
				glColor3f(r, g, b);

				// ��������������
				glVertex3f(x0 + x, y0 + y, z0 + z);
				glVertex3f(x1 + x, y1 + y, z1 + z);
				glVertex3f(zr0 * cos(2 * M_PI * (float)(j + 1) / slices) + x,
					zr0 * sin(2 * M_PI * (float)(j + 1) / slices) + y,
					z0 + z);

				glVertex3f(x1 + x, y1 + y, z1 + z);
				glVertex3f(zr1 * cos(2 * M_PI * (float)(j + 1) / slices) + x,
					zr1 * sin(2 * M_PI * (float)(j + 1) / slices) + y,
					z1 + z);
				glVertex3f(zr0 * cos(2 * M_PI * (float)(j + 1) / slices) + x,
					zr0 * sin(2 * M_PI * (float)(j + 1) / slices) + y,
					z0 + z);
			}
		}

		glEnd();
	}


    void Draw() override {
        DrawSphere(radius, x, y, z, r, g, b);
    }

};