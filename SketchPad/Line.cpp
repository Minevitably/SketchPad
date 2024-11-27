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
	// TODO: �ڴ���������������
}

// �Ľ���Bresenham���ƺ�ɫֱ��
void Line::DrawBasicBrelinePro(CDC* pDC) const
{
	// TODO: �ڴ���������������
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