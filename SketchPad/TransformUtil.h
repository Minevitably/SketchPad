#pragma once
#include <vector>

class TransformUtil
{
public:
	static std::vector<CPoint> TransformUtil::Translate(std::vector<CPoint> points, int tx, int ty);

	static std::vector<CPoint> TransformUtil::Scale(std::vector<CPoint> points, float sx, float sy);

	static std::vector<CPoint> TransformUtil::Shear(std::vector<CPoint> points, float sh);

	static std::vector<CPoint> TransformUtil::Reflect(std::vector<CPoint> points);

	static std::vector<CPoint> TransformUtil::Rotate(std::vector<CPoint> points, float angle);

	static std::vector<CPoint> TransformUtil::ScaleAndShear(std::vector<CPoint> points, float sx, float sy, float sh);

	static std::vector<CPoint> TransformUtil::RotateByPoint(std::vector<CPoint> points, float angle, float px, float py);

	static std::vector<CPoint> TransformUtil::ReflectByYX(std::vector<CPoint> points);

	static std::vector<CPoint> TransformUtil::Apply(std::vector<CPoint> points, float matrix[3][3]);



};

