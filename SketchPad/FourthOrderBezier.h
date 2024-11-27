#pragma once
#include "Graphic.h"


class FourthOrderBezier : public Graphic {
public:
    FourthOrderBezier(std::vector<CPoint> points); // ���캯��
    void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
    std::vector<CPoint> GetPoints() override; // getter���������ص㼯
    void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯

private:
    std::vector<CPoint> m_points; // �洢��ļ���
};

