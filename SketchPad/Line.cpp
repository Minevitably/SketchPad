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

// DDA��������Ϊ���ߵ�ֱ��
void Line::DrawBasicDdaline(CDC* pDC) const
{
	// ���������յ�
	CPoint start = m_points[0];
	CPoint end = m_points[1];
	// TODO: �ڴ˴����ʵ�ִ���.
	// �����߶ε�����
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	int steps = Max(abs(dx), abs(dy)); // ���㲽��
	float xIncrement = static_cast<float>(dx) / steps; // X����
	float yIncrement = static_cast<float>(dy) / steps; // Y����

	// ʹ�� DDA �㷨��������
	float x = start.x;
	float y = start.y;
	for (int i = 0; i <= steps; i++)
	{
		// ���㵱ǰ��
		int currentX = static_cast<int>(round(x));
		int currentY = static_cast<int>(round(y));

		// �ж��Ƿ���Ƹõ㣨�����߼���
		if (i % 10 < 5) // ÿ10�����л���ǰ5����
		{
			// �� pDC �ϻ��Ƶ�ǰ��
			pDC->SetPixel(currentX, currentY, RGB(0, 0, 0)); // ���ƺ�ɫ����
		}

		// ��������
		x += xIncrement;
		y += yIncrement;
	}

}

// Bresenham�����߿�Ϊ2��ֱ��
void Line::DrawBasicBreline(CDC* pDC) const
{
	// ���������յ�
	CPoint start = m_points[0];
	CPoint end = m_points[1];

	// �����߶ε�����
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	// �������ֵ
	int abs_dx = std::abs(dx);
	int abs_dy = std::abs(dy);

	// ���㲽��
	int steps = Max(abs_dx, abs_dy);

	// ��������
	float xIncrement = static_cast<float>(dx) / steps;
	float yIncrement = static_cast<float>(dy) / steps;

	// ��ǰ�������
	float x = start.x;
	float y = start.y;

	// �߿�����Ϊ 2������������Ҫ�����ߵ������������
	for (int i = 0; i <= steps; i++)
	{
		// �������뵱ǰ��
		int currentX = static_cast<int>(round(x));
		int currentY = static_cast<int>(round(y));

		// �����߿�Ϊ 2 ��ֱ��
		// �ڵ�ǰ������¸�����һ������
		pDC->SetPixel(currentX, currentY, RGB(0, 0, 0)); // ����
		pDC->SetPixel(currentX, currentY + 1, RGB(0, 0, 0)); // �Ϸ�
		pDC->SetPixel(currentX, currentY - 1, RGB(0, 0, 0)); // �·�

		// ��������
		x += xIncrement;
		y += yIncrement;
	}
}

// �Ľ���Bresenham���ƺ�ɫֱ��
void Line::DrawBasicBrelinePro(CDC* pDC) const
{
	// ���������յ�
	CPoint start = m_points[0];
	CPoint end = m_points[1];

	// ��������
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	int abs_dx = std::abs(dx);
	int abs_dy = std::abs(dy);

	// ȷ�����Ʒ���
	int sx = (dx >= 0) ? 1 : -1; // x����Ĳ���
	int sy = (dy >= 0) ? 1 : -1; // y����Ĳ���

	// ��ʼ�����
	int err = abs_dx - abs_dy;

	// �����߶�
	while (true)
	{
		// ���Ƶ�ǰ��
		pDC->SetPixel(start.x, start.y, RGB(255, 0, 0)); // ��ɫ����

		// ��������յ㣬ֹͣ����
		if (start.x == end.x && start.y == end.y) break;

		// �������
		int e2 = err * 2;

		// ѡ��ˮƽ��ֱ�ƶ�
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

// ϵͳ�⺯������ֱ��
void Line::DrawBasicSysline(CDC* pDC) const
{
	// TODO: �ڴ���������������
	CPen solidPen(PS_SOLID, 1, RGB(0, 255, 0));  // ʵ�ߣ���ɫ
	CPen* oldPen = pDC->SelectObject(&solidPen); // ѡ��ʵ�߻���

	pDC->MoveTo((m_points)[0]);
	pDC->LineTo((m_points)[1]);

	pDC->SelectObject(oldPen);
}