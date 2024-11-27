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
	// 获取起点和终点
	CPoint start = m_points[0];
	CPoint end = m_points[1];

	// 计算增量
	int dx = abs(end.x - start.x);
	int dy = abs(end.y - start.y);

	// 判断主轴方向
	bool isSteep = (dy > dx); // 判断是否以 y 为主轴

	// 如果以 y 为主轴，交换 x 和 y 的处理
	if (isSteep) {
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
		std::swap(dx, dy);
	}

	// 确定绘制方向
	int xStep = (start.x < end.x) ? 1 : -1;
	int yStep = (start.y < end.y) ? 1 : -1;

	// 初始化变量
	int d = 2 * dy - dx; // 初始误差
	int x = start.x, y = start.y;

	// 循环绘制
	for (int i = 0; i <= dx; i++) {
		// 绘制像素（如果主轴是 y，需交换回原始坐标）
		if (isSteep) {
			pDC->SetPixel(y, x - 1, RGB(0, 0, 0));
			pDC->SetPixel(y, x, RGB(0, 0, 0));
			pDC->SetPixel(y, x + 1, RGB(0, 0, 0));
		}
		else {
			pDC->SetPixel(x, y - 1, RGB(0, 0, 0));
			pDC->SetPixel(x, y, RGB(0, 0, 0));
			pDC->SetPixel(x, y + 1, RGB(0, 0, 0));
		}

		// 判断误差并调整
		if (d >= 0) {
			y += yStep;        // 调整次方向
			d -= 2 * dx;       // 减去 dx
		}
		d += 2 * dy;           // 增加 dy
		x += xStep;            // 增加主方向
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