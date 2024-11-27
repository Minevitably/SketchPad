#pragma once
#include "Graphic.h"
namespace MyGraphics {
	class Polygon : public Graphic {
	public:
		Polygon(std::vector<CPoint> points); // ���캯��
		void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
		std::vector<CPoint> GetPoints() override; // getter���������ص㼯
		void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯

		void Draw(CDC* pDC, COLORREF color) const;
		void Clip(const CRect& clipRect);

	private:
		std::vector<CPoint> m_points; // �洢��ļ���
		// �жϵ��Ƿ���ָ���߽���
		static bool IsInside(const CPoint& p, const CRect& rect, int edge);
		// ����߽������αߵĽ���
		static CPoint ComputeIntersection(const CPoint& p1, const CPoint& p2, const CRect& rect, int edge);
	};
}