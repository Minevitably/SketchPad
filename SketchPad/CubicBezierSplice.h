#pragma once
#include "Graphic.h"

class CubicBezierSplice : public Graphic {
public:
    CubicBezierSplice(std::vector<CPoint> points); // ���캯��
    void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
    std::vector<CPoint> GetPoints() override; // getter���������ص㼯
    void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯

    CPoint CalculateCubicBezierPoint(CPoint p0, CPoint p1, CPoint p2, CPoint p3, float t) const;
private:
    std::vector<CPoint> m_points; // �洢��ļ���
};
