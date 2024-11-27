#pragma once
#include "Graphic.h"

namespace MyGraphics {
    class Ellipse :public Graphic
    {
    public:
        Ellipse(std::vector<CPoint> points, int a, int b); // ���캯��
        void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
        std::vector<CPoint> GetPoints() override; // getter���������ص㼯
        void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯


    private:
        std::vector<CPoint> m_points; // �洢��ļ���
        int m_a;
        int m_b;
    };
}