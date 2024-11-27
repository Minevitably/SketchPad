#pragma once
#include "Graphic.h"


#define DDA_LINE 0
#define BRE_LINE 1
#define BRE_LINE_PRO 2
#define SYS_LINE 3

class Line : public Graphic {
public:
    Line(std::vector<CPoint> points, int algo); // ���캯��
    void Draw(CDC* pDC) const override; // ʹ��pDC����ͼ��
    std::vector<CPoint> GetPoints() override; // getter���������ص㼯
    void SetPoints(std::vector<CPoint> points) override; // setter���������õ㼯

    void SetAlgo(int algo) ;
    void DrawBasicDdaline(CDC* pDC) const;
    void DrawBasicBreline(CDC* pDC) const;
    void DrawBasicBrelinePro(CDC* pDC) const;
    void DrawBasicSysline(CDC* pDC) const;
private:
    std::vector<CPoint> m_points; // �洢��ļ���
    int algo;
};

