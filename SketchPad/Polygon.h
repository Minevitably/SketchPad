#pragma once
#include "Graphic.h"
namespace MyGraphics {
	class Polygon : public Graphic {
	public:
		Polygon(std::vector<CPoint> points); // 构造函数
		void Draw(CDC* pDC) const override; // 使用pDC绘制图形
		std::vector<CPoint> GetPoints() override; // getter方法，返回点集
		void SetPoints(std::vector<CPoint> points) override; // setter方法，设置点集

		void Draw(CDC* pDC, COLORREF color) const;
		void Clip(const CRect& clipRect);

	private:
		std::vector<CPoint> m_points; // 存储点的集合
		// 判断点是否在指定边界内
		static bool IsInside(const CPoint& p, const CRect& rect, int edge);
		// 计算边界与多边形边的交点
		static CPoint ComputeIntersection(const CPoint& p1, const CPoint& p2, const CRect& rect, int edge);
	};
}