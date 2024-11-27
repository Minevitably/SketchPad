#pragma once
#include "Graphic.h"

namespace MyGraphics {
    class Ellipse :public Graphic
    {
    public:
        Ellipse(std::vector<CPoint> points, int a, int b); // 构造函数
        void Draw(CDC* pDC) const override; // 使用pDC绘制图形
        std::vector<CPoint> GetPoints() override; // getter方法，返回点集
        void SetPoints(std::vector<CPoint> points) override; // setter方法，设置点集


    private:
        std::vector<CPoint> m_points; // 存储点的集合
        int m_a;
        int m_b;
    };
}