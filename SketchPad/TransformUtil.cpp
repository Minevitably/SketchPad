#include "pch.h"
#include "TransformUtil.h"

std::vector<CPoint> TransformUtil::Translate(std::vector<CPoint> points, int tx, int ty)
{
	// 平移矩阵
	float translationMatrix[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{tx, ty, 1}
	};
	return Apply(points, translationMatrix);
}


std::vector<CPoint> TransformUtil::Scale(std::vector<CPoint> points, float sx, float sy)
{
	// 比例矩阵
	float scalingMatrix[3][3] = {
		{sx, 0, 0},
		{0, sy, 0},
		{0, 0, 1}
	};

	return Apply(points, scalingMatrix);
}


std::vector<CPoint> TransformUtil::Shear(std::vector<CPoint> points, float sh)
{
	// 错切矩阵
	float shearMatrix[3][3] = {
		{1, sh, 0},
		{0, 1, 0},
		{0, 0, 1}
	};

	return Apply(points, shearMatrix);
}

std::vector<CPoint> TransformUtil::Reflect(std::vector<CPoint> points)
{
	// 对称矩阵
	float reflectionMatrix[3][3] = {
		{0, -1, 0},
		{-1, 0, 0},
		{0, 0, 1}
	};

	return Apply(points, reflectionMatrix);
}

std::vector<CPoint> TransformUtil::Rotate(std::vector<CPoint> points, float angle)
{
	float radians = angle * (3.14159 / 180); // 转换为弧度
	float cosA = cos(radians);
	float sinA = sin(radians);

	// 旋转矩阵
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
	// 这里的矩阵是用逆时针旋转矩阵计算出来的，所以角度要传入负数
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
	// 对称矩阵
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
		// 将点转换为齐次坐标
		float x = point.x;
		float y = point.y;
		float newX = matrix[0][0] * x + matrix[1][0] * y + matrix[2][0];
		float newY = matrix[0][1] * x + matrix[1][1] * y + matrix[2][1];

		// 更新点
		point.x = static_cast<int>(newX);
		point.y = static_cast<int>(newY);
		newPoints.push_back(point);
	}
	return newPoints;
}
