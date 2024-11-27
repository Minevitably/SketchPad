#pragma once
#include "Graphic.h"
class Hexagon : public Graphic
{
public:
    Hexagon(std::vector<CPoint> points, int m_radius, bool m_raw); // ���캯��
    void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
    std::vector<CPoint> GetPoints() override; // getter���������ص㼯
    void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯


private:
    std::vector<CPoint> m_points; // �洢��ļ���
    int m_radius;
    bool m_raw;
};

