#pragma once
#include "Graphic.h"


#define DDA_LINE 0
#define BRE_LINE 1
#define BRE_LINE_PRO 2
#define SYS_LINE 3

class Line : public Graphic {
public:
    Line(std::vector<CPoint> points, int algo); // 构造函数
    void Draw(CDC* pDC) const override; // 使用pDC绘制图形
    std::vector<CPoint> GetPoints() override; // getter方法，返回点集
    void SetPoints(std::vector<CPoint> points) override; // setter方法，设置点集

    void SetAlgo(int algo) ;
    void DrawBasicDdaline(CDC* pDC) const;
    void DrawBasicBreline(CDC* pDC) const;
    void DrawBasicBrelinePro(CDC* pDC) const;
    void DrawBasicSysline(CDC* pDC) const;
private:
    std::vector<CPoint> m_points; // 存储点的集合
    int algo;
};

