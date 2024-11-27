#pragma once
#include "Graphic.h"


class CubicBspline : public Graphic {
public:
    CubicBspline(std::vector<CPoint> points); // ���캯��
    void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
    std::vector<CPoint> GetPoints() override; // getter���������ص㼯
    void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯

    CPoint CalculateCubicBsplinePoint(int i, float t) const;
private:
    std::vector<CPoint> m_points; // �洢��ļ���
};

