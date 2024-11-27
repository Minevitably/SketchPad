#pragma once
#include <vector>
#include <afxwin.h> 

class Graphic {
public:
    virtual void Draw(CDC* pDC) const = 0; // ʹ��pDC����ͼ��
    virtual std::vector<CPoint> GetPoints() = 0; // getter���������ص㼯
    virtual void SetPoints(std::vector<CPoint> points) = 0; // setter���������õ㼯
    virtual ~Graphic() {} // ����������
};