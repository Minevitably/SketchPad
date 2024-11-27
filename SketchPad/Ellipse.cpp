#include "pch.h"
#include "Ellipse.h"


namespace MyGraphics {
    Ellipse::Ellipse(std::vector<CPoint> points, int a, int b) {
        this->m_points = points;
        this->m_a = a;
        this->m_b = b;
    }

    void Ellipse::Draw(CDC* pDC) const {
        // ��Բ�����ġ�����Ͷ���
        CPoint center = m_points[0]; // ��Բ����
        int a = m_a; // ���ᣨˮƽ���ᣩ
        int b = m_b; // ���ᣨ��ֱ���ᣩ

        // ��ʼ������;��߲���
        int x = 0;
        int y = b;
        int a2 = a * a;
        int b2 = b * b;
        int fa2 = 4 * a2;
        int fb2 = 4 * b2;
        int d = 0;

        // ��һ�׶Σ�������Բ���ϰ벿��
        while (a2 * y > b2 * x) {
            // ���ƶԳƵ�
            pDC->SetPixel(center.x + x, center.y + y, RGB(0, 0, 0)); // ��һ����
            pDC->SetPixel(center.x - x, center.y + y, RGB(0, 0, 0)); // �ڶ�����
            pDC->SetPixel(center.x + x, center.y - y, RGB(0, 0, 0)); // ��������
            pDC->SetPixel(center.x - x, center.y - y, RGB(0, 0, 0)); // ��������

            // ���¾��߲���
            d += fb2 * x + b2;
            if (d > 0) {
                y--;
                d -= fa2 * y;
            }
            x++;
        }

        // �ڶ��׶Σ�������Բ���°벿��
        d = 0;
        x = a;
        y = 0;

        while (b2 * x > a2 * y) {
            // ���ƶԳƵ�
            pDC->SetPixel(center.x + x, center.y + y, RGB(0, 0, 0)); // ��һ����
            pDC->SetPixel(center.x - x, center.y + y, RGB(0, 0, 0)); // �ڶ�����
            pDC->SetPixel(center.x + x, center.y - y, RGB(0, 0, 0)); // ��������
            pDC->SetPixel(center.x - x, center.y - y, RGB(0, 0, 0)); // ��������

            // ���¾��߲���
            d += fa2 * y + a2;
            if (d > 0) {
                x--;
                d -= fb2 * x;
            }
            y++;
        }
    }

    std::vector<CPoint> Ellipse::GetPoints() {
        return m_points;
    }

    void Ellipse::SetPoints(std::vector<CPoint> points) {
        m_points.push_back(points[0]);
    }
}