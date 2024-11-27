#include "pch.h"
#include "TransformUtil.h"

std::vector<CPoint> TransformUtil::Translate(std::vector<CPoint> points, int tx, int ty)
{
	// ƽ�ƾ���
	float translationMatrix[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{tx, ty, 1}
	};
	return Apply(points, translationMatrix);
}


std::vector<CPoint> TransformUtil::Scale(std::vector<CPoint> points, float sx, float sy)
{
	// ��������
	float scalingMatrix[3][3] = {
		{sx, 0, 0},
		{0, sy, 0},
		{0, 0, 1}
	};

	return Apply(points, scalingMatrix);
}


std::vector<CPoint> TransformUtil::Shear(std::vector<CPoint> points, float sh)
{
	// ���о���
	float shearMatrix[3][3] = {
		{1, sh, 0},
		{0, 1, 0},
		{0, 0, 1}
	};

	return Apply(points, shearMatrix);
}

std::vector<CPoint> TransformUtil::Reflect(std::vector<CPoint> points)
{
	// �Գƾ���
	float reflectionMatrix[3][3] = {
		{0, -1, 0},
		{-1, 0, 0},
		{0, 0, 1}
	};

	return Apply(points, reflectionMatrix);
}

std::vector<CPoint> TransformUtil::Rotate(std::vector<CPoint> points, float angle)
{
	float radians = angle * (3.14159 / 180); // ת��Ϊ����
	float cosA = cos(radians);
	float sinA = sin(radians);

	// ��ת����
	float rotationMatrix[3][3] = {
		{cosA, -sinA, 0},
		{sinA, cosA, 0},
		{0, 0, 1}
	};

	return Apply(points, rotationMatrix);
}

std::vector<CPoint> TransformUtil::ScaleAndShear(std::vector<CPoint> points, float sx, float sy, float sh) {
	float composite[3][3] = {
		{sx, sh * sy, 0},
		{0, sy, 0},
		{0, 0, 1}
	};

	return Apply(points, composite);
}

std::vector<CPoint> TransformUtil::RotateByPoint(std::vector<CPoint> points, float angle, float px, float py)
{
	// ����ľ���������ʱ����ת�����������ģ����ԽǶ�Ҫ���븺��
	angle = angle * (3.14159 / 180);
	float cosA = cos(angle);
	float sinA = sin(angle);

	float composite[3][3] = {
		{cosA, sinA, 0},
		{-sinA, cosA, 0},
		{px - px * cosA + py * sinA, py - py * cosA - px * sinA, 1}
	};

	return Apply(points, composite);
}

std::vector<CPoint> TransformUtil::ReflectByYX(std::vector<CPoint> points)
{
	// �Գƾ���
	float composite[3][3] = {
		{0, 1, 0},
		{1, 0, 0},
		{0, 0, 1}
	};

	return Apply(points, composite);
}

std::vector<CPoint> TransformUtil::Apply(std::vector<CPoint> points, float matrix[3][3])
{
	std::vector<CPoint> newPoints;
	for (CPoint point : points) {
		// ����ת��Ϊ�������
		float x = point.x;
		float y = point.y;
		float newX = matrix[0][0] * x + matrix[1][0] * y + matrix[2][0];
		float newY = matrix[0][1] * x + matrix[1][1] * y + matrix[2][1];

		// ���µ�
		point.x = static_cast<int>(newX);
		point.y = static_cast<int>(newY);
		newPoints.push_back(point);
	}
	return newPoints;
}
