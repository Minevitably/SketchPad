#pragma once
#include <vector>
#include <afxwin.h> 

class Graphic {
public:
    virtual void Draw(CDC* pDC) const = 0; // 使用pDC绘制图形
    virtual std::vector<CPoint> GetPoints() = 0; // getter方法，返回点集
    virtual void SetPoints(std::vector<CPoint> points) = 0; // setter方法，设置点集
    virtual ~Graphic() {} // 虚析构函数
};