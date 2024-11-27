#include "pch.h"
#include "Line.h"

inline int Max(int a, int b) {
	return (a > b) ? a : b;
}

Line::Line(std::vector<CPoint> points, int algo) {
	this->m_points = points;
	this->algo = algo;
}

void Line::Draw(CDC* pDC) const {
	switch (algo) {
	case DDA_LINE:
		DrawBasicDdaline(pDC);
		break;
	case BRE_LINE:
		DrawBasicBreline(pDC);
		break;
	case BRE_LINE_PRO:
		DrawBasicBrelinePro(pDC);
		break;
	case SYS_LINE:
		DrawBasicSysline(pDC);
		break;
	default:
		AfxMessageBox(_T("wrong"));
		break;
	}
}

std::vector<CPoint> Line::GetPoints() {
    return m_points;
}

void Line::SetPoints(std::vector<CPoint> points) {
	m_points.push_back(points[0]);
	m_points.push_back(points[1]);
}

void Line::SetAlgo(int algo) {
	this->algo = algo;
}

// DDA绘制线型为虚线的直线
void Line::DrawBasicDdaline(CDC* pDC) const
{
	// 定义起点和终点
	CPoint start = m_points[0];
	CPoint end = m_points[1];
	// TODO: 在此处添加实现代码.
	// 计算线段的增量
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	int steps = Max(abs(dx), abs(dy)); // 计算步数
	float xIncrement = static_cast<float>(dx) / steps; // X增量
	float yIncrement = static_cast<float>(dy) / steps; // Y增量

	// 使用 DDA 算法绘制虚线
	float x = start.x;
	float y = start.y;
	for (int i = 0; i <= steps; i++)
	{
		// 计算当前点
		int currentX = static_cast<int>(round(x));
		int currentY = static_cast<int>(round(y));

		// 判断是否绘制该点（虚线逻辑）
		if (i % 10 < 5) // 每10个点中绘制前5个点
		{
			// 在 pDC 上绘制当前点
			pDC->SetPixel(currentX, currentY, RGB(0, 0, 0)); // 绘制黑色像素
		}

		// 增加增量
		x += xIncrement;
		y += yIncrement;
	}

}

// Bresenham绘制线宽为2的直线
void Line::DrawBasicBreline(CDC* pDC) const
{
	// 定义起点和终点
	CPoint start = m_points[0];
	CPoint end = m_points[1];

	// 计算线段的增量
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	// 计算绝对值
	int abs_dx = std::abs(dx);
	int abs_dy = std::abs(dy);

	// 计算步数
	int steps = Max(abs_dx, abs_dy);

	// 计算增量
	float xIncrement = static_cast<float>(dx) / steps;
	float yIncrement = static_cast<float>(dy) / steps;

	// 当前点的坐标
	float x = start.x;
	float y = start.y;

	// 线宽设置为 2，所以我们需要在主线的两侧绘制像素
	for (int i = 0; i <= steps; i++)
	{
		// 四舍五入当前点
		int currentX = static_cast<int>(round(x));
		int currentY = static_cast<int>(round(y));

		// 绘制线宽为 2 的直线
		// 在当前点的上下各绘制一个像素
		pDC->SetPixel(currentX, currentY, RGB(0, 0, 0)); // 主线
		pDC->SetPixel(currentX, currentY + 1, RGB(0, 0, 0)); // 上方
		pDC->SetPixel(currentX, currentY - 1, RGB(0, 0, 0)); // 下方

		// 增加增量
		x += xIncrement;
		y += yIncrement;
	}
}

// 改进的Bresenham绘制红色直线
void Line::DrawBasicBrelinePro(CDC* pDC) const
{
	// 定义起点和终点
	CPoint start = m_points[0];
	CPoint end = m_points[1];

	// 计算增量
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	int abs_dx = std::abs(dx);
	int abs_dy = std::abs(dy);

	// 确定绘制方向
	int sx = (dx >= 0) ? 1 : -1; // x方向的步进
	int sy = (dy >= 0) ? 1 : -1; // y方向的步进

	// 初始化误差
	int err = abs_dx - abs_dy;

	// 绘制线段
	while (true)
	{
		// 绘制当前点
		pDC->SetPixel(start.x, start.y, RGB(255, 0, 0)); // 红色像素

		// 如果到达终点，停止绘制
		if (start.x == end.x && start.y == end.y) break;

		// 计算误差
		int e2 = err * 2;

		// 选择水平或垂直移动
		if (e2 > -abs_dy) {
			err -= abs_dy;
			start.x += sx;
		}
		if (e2 < abs_dx) {
			err += abs_dx;
			start.y += sy;
		}
	}
}

// 系统库函数绘制直线
void Line::DrawBasicSysline(CDC* pDC) const
{
	// TODO: 在此添加命令处理程序代码
	CPen solidPen(PS_SOLID, 1, RGB(0, 255, 0));  // 实线，绿色
	CPen* oldPen = pDC->SelectObject(&solidPen); // 选择实线画笔

	pDC->MoveTo((m_points)[0]);
	pDC->LineTo((m_points)[1]);

	pDC->SelectObject(oldPen);
}