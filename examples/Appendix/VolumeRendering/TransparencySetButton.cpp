/**********************************************************************

  �ļ���: TransparencySetButton.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

// TransparencySetButton.cpp : implementation file
//

#include "stdafx.h"
#include "TransparencySetButton.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FLAG_HALF_WIDTH 10

/////////////////////////////////////////////////////////////////////////////
// CTransparencySetButton

CTransparencySetButton::CTransparencySetButton()
{
	//���δ����
	m_IsLButtonDown = false;

	m_KeyPointSet.Add(CPoint(0, 0));
	m_Max = 1;
	m_Min = 0;
	m_Histogram = 0;
	m_KeyPointIndex = -1;
}

CTransparencySetButton::~CTransparencySetButton()
{
}

BEGIN_MESSAGE_MAP(CTransparencySetButton, CButton)
	//{{AFX_MSG_MAP(CTransparencySetButton)
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CTransparencySetButton::SetHistogram(double grayMin, double grayMax, unsigned long *histogram)
{
	m_Max = grayMax;
	m_Min = grayMin;
	m_Histogram = histogram;

	m_FreqMax = GetMaxFreqOfHistogram();

	this->Invalidate();
	AfxGetMainWnd()->PostMessage(WM_UPDATE_OPACITY_VIEW_MSG, 0, 0);
}

bool CTransparencySetButton::GetCurrentKeyPoint(double&gray, double&opacity)
{
	if (m_KeyPointIndex == -1 || 
		m_KeyPointSet.GetSize() <= 0 ||
		m_KeyPointIndex >= m_KeyPointSet.GetSize()) return false;

	CRect rect;
	GetClientRect(rect);

	CPoint p = m_KeyPointSet.GetAt(m_KeyPointIndex);
	gray = (float)p.x/(float)rect.Width()*(m_Max-m_Min)+m_Min;
	opacity = 1-(float)p.y/(float)rect.Height();

	return true;
}

void CTransparencySetButton::SetKeyPoint(double gray, double opacity)
{
	if(gray < m_Min || gray > m_Max) return;
	if(opacity <0 || opacity > 1) return;
	CRect rect;
	GetClientRect(rect);

	int x = (gray-m_Min)/(m_Max-m_Min)*rect.Width();
	int y = (1-opacity)*rect.Height();

	int num = m_KeyPointSet.GetSize();
	for (int i=0; i<num; i++)
	{
		if(fabs(double(m_KeyPointSet.GetAt(i).x - x)) <FLAG_HALF_WIDTH)
		{
			CPoint pt(x,y);
			m_KeyPointSet.SetAt(i, pt);
			Invalidate();

			AfxGetMainWnd()->PostMessage(WM_UPDATE_OPACITY_VIEW_MSG, 0, 0);
			break;
		}
	}
}

void CTransparencySetButton::GetKeyPointPair(std::vector<std::pair<double, double>>& keyPair)
{
	CRect rect;
	GetClientRect(rect);

	for (int i=0; i<m_KeyPointSet.GetSize(); i++)
	{
		CPoint p = m_KeyPointSet.GetAt(i);
		double gray = (float)p.x/(float)rect.Width()*(m_Max-m_Min)+m_Min;
		double opacity = 1-(float)p.y/(float)rect.Height();
		keyPair.push_back(std::make_pair(gray, opacity));
	}

}


/////////////////////////////////////////////////////////////////////////////
// CTransparencySetButton message handlers

int CTransparencySetButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CTransparencySetButton::OnDestroy()
{
	CButton::OnDestroy();

	// TODO: Add your message handler code here

	
}

void CTransparencySetButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CTransparencySetButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect Rc= lpDrawItemStruct->rcItem ;

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC,Rc.Width(),Rc.Height());

	//��λͼѡ�뵽�ڴ���ʾ�豸��
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);


	//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ  
	MemDC.FillSolidRect(Rc,RGB(255,255,255));

	DrawGrayHistogram(pDC, Rc);
	DrawTransparencyCurve(pDC, Rc);

	CBrush frame(RGB(0,0,0));
    MemDC.FrameRect(&lpDrawItemStruct->rcItem, &frame);

	//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ  
	///MemDC.FillSolidRect(Rc,RGB(255,255,255));

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	pDC->BitBlt(0,0,Rc.Width(),Rc.Height(),&MemDC,0,0,SRCCOPY);
	//��ͼ��ɺ������

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

float CTransparencySetButton::GetMaxFreqOfHistogram()
{
	unsigned long max=0;
	for (unsigned long i=0; i<32768+1+65535; i++)
	{
		if (max < m_Histogram[i]) max = m_Histogram[i];
	}
	return 1.0/log(double(max));
}

float CTransparencySetButton::GetRelativeBin( double left, double right ) const
{
	int iLeft = floorf(left);
	int iRight = ceilf(right);

	unsigned long maximum = 0;

	for( int i = iLeft; i <= iRight ; i++)
	{
		int posInArray = i + 32768;
		if( m_Histogram[posInArray] > maximum ) maximum = m_Histogram[posInArray];
	}

	return float(log(double(maximum))*m_FreqMax);
}

void CTransparencySetButton::DrawGrayHistogram(CDC *pDC, CRect &Rc)
{
	CPen penBlack(PS_SOLID, 1, RGB(160, 160, 164));
	CPen* pOldPen = MemDC.SelectObject(&penBlack);


	double step = (m_Max-m_Min)/double(Rc.Width());

	double pos = m_Min;
	
	for (int x = 0; x < Rc.Width(); x++)
	{
		double left = pos;
		double right = pos + step;

		float height = GetRelativeBin( left , right );

		if (height >= 0)
		{   
			MemDC.MoveTo(x,Rc.Height()*(1-height));
			MemDC.LineTo(x,Rc.Height());
		}
		pos += step;
	}

	MemDC.SelectObject(pOldPen);
}

void CTransparencySetButton::DrawTransparencyCurve(CDC *pDC,CRect &Rc)
{

	//draw lines according to the key points
	
	CPen penBlack(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* pOldPen = MemDC.SelectObject(&penBlack);

	// and a solid red brush
	CBrush brushRed(RGB(0, 255, 0));
	CBrush* pOldBrush = MemDC.SelectObject(&brushRed);

	int KeyPointNum = m_KeyPointSet.GetSize();

	if (KeyPointNum == 0) return;
	if (KeyPointNum == 1)
	{
		CPoint p1(0, m_KeyPointSet[0].y) ;
		CPoint p2(Rc.Width(), m_KeyPointSet[0].y);

		MemDC.MoveTo(p1);
		MemDC.LineTo(p2);

		CPoint p = m_KeyPointSet[0];
		MemDC.Ellipse(p.x-5,p.y-5, p.x+5, p.y+5);
	}
	else
	{
		//draw the lines lower than the first point and higher than the second point
		CPoint pf1(0, m_KeyPointSet.GetAt(0).y);
		CPoint pf2 = m_KeyPointSet.GetAt(0);
		MemDC.MoveTo(pf1);
		MemDC.LineTo(pf2);

		
		CPoint pl1 = m_KeyPointSet.GetAt(KeyPointNum-1);
		CPoint pl2(Rc.Width(), m_KeyPointSet.GetAt(KeyPointNum-1).y);
		MemDC.MoveTo(pl1);
		MemDC.LineTo(pl2);

		for (int i=0; i<KeyPointNum-1; i++)
		{
			CPoint p1 = m_KeyPointSet[i];
			CPoint p2 = m_KeyPointSet[i+1];

			MemDC.MoveTo(p1);
			MemDC.LineTo(p2);
		}

		for (int i=0; i<KeyPointNum; i++)
		{
			CPoint p = m_KeyPointSet[i];
			MemDC.Ellipse(p.x-5,p.y-5, p.x+5, p.y+5);
		}
	}

	// Put back the old objects.
	MemDC.SelectObject(pOldPen);
	MemDC.SelectObject(pOldBrush);
}

//�õ��ؼ�������
int  CTransparencySetButton::GetSelectedKeyPointIndex(const CPoint point)
{
	if(m_KeyPointSet.GetSize()<=1) return -1;

	//�ҵ�ֵ����Ĺؼ���
	int     minClose  = -1;

	int KeyPointNum = m_KeyPointSet.GetSize();
	for ( int i=0; i<KeyPointNum; i++)
	{
		float dis = sqrt(pow((float)(point.x-m_KeyPointSet.GetAt(i).x), 2) + pow((float)(point.y-m_KeyPointSet.GetAt(i).y), 2));
		if (dis < FLAG_HALF_WIDTH)
		{
			minClose = i;
			break;
		}
	}

	return minClose;
}

void CTransparencySetButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//�õ��ؼ��������
	m_KeyPointIndex = GetSelectedKeyPointIndex(point);

	int KeyPointNum = m_KeyPointSet.GetSize();

	if (m_KeyPointIndex >= 0){
		//��־��갴��
		m_IsLButtonDown = true;
	}
	else
	{
		//add a key point
		if (KeyPointNum == 0 ){
			m_KeyPointSet.InsertAt(0, point);
		}
		else
		{
			if ( m_KeyPointSet.GetAt(0).x-point.x > FLAG_HALF_WIDTH){
				m_KeyPointSet.InsertAt(0, point);
			}

			if (point.x - m_KeyPointSet.GetAt(KeyPointNum-1).x > FLAG_HALF_WIDTH){
				m_KeyPointSet.InsertAt(KeyPointNum, point);
			}

			for (int i=0; i<KeyPointNum-1; i++)
			{
				CPoint p1 = m_KeyPointSet.GetAt(i);
				CPoint p2 = m_KeyPointSet.GetAt(i+1);

				if (point.x-p1.x > FLAG_HALF_WIDTH && p2.x-point.x>FLAG_HALF_WIDTH){
					m_KeyPointSet.InsertAt(i+1, point);
				}		
			}
		}
	}
	this->Invalidate();

	//////////////////////////////////////////////////////////////////////////
}

void CTransparencySetButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnLButtonUp(nFlags, point);

	//�������
	m_IsLButtonDown = false;

	m_KeyPointIndex = GetSelectedKeyPointIndex(point);

	AfxGetMainWnd()->PostMessage(WM_UPDATE_OPACITY_VIEW_MSG, 0, 0);
	AfxGetMainWnd()->PostMessage(WM_UPDATE_OPACITY_INFO_MSG, 0, 0);
}

void CTransparencySetButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CButton::OnRButtonDown(nFlags, point);

	//�ҵ����index
	m_KeyPointIndex = GetSelectedKeyPointIndex(point);

	if (m_KeyPointIndex == -1) return;
	if (m_KeyPointSet.GetSize() == 1) return;


	//ɾ����Ӧ�ĵ�
	m_KeyPointSet.RemoveAt(m_KeyPointIndex);
	this->Invalidate();

	AfxGetMainWnd()->PostMessage(WM_UPDATE_OPACITY_VIEW_MSG, 0, 0);
}

//�϶��ؼ���
void CTransparencySetButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CButton::OnMouseMove(nFlags, point);

	if (m_KeyPointIndex == -1) return;
	if (m_KeyPointSet.GetSize() == 1) return;
	if (!m_IsLButtonDown) return;

	if (m_KeyPointIndex == 0)
	{
		CPoint p1 = m_KeyPointSet.GetAt(1);
		if (p1.x-point.x> FLAG_HALF_WIDTH)
		{
			m_KeyPointSet.SetAt(m_KeyPointIndex, point);
			Invalidate();
		}
	}
	else
	if (m_KeyPointIndex == m_KeyPointSet.GetSize()-1)
	{
		CPoint p1 = m_KeyPointSet.GetAt(m_KeyPointSet.GetSize()-2);
		if (point.x - p1.x > FLAG_HALF_WIDTH)
		{
			m_KeyPointSet.SetAt(m_KeyPointIndex, point);
			Invalidate();
		}
	}

	else{
		//ȷ���϶���Χ�ڽ���
		CPoint p1 = m_KeyPointSet.GetAt(m_KeyPointIndex-1);
		CPoint p2 =m_KeyPointSet.GetAt(m_KeyPointIndex+1);
		if((point.x-p1.x > FLAG_HALF_WIDTH) && (p2.x-point.x > FLAG_HALF_WIDTH))
		{
			m_KeyPointSet.SetAt(m_KeyPointIndex, point);
			Invalidate();
		}		
	}
}

BOOL CTransparencySetButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	/*CRect   rect; 
	GetClientRect(rect); 
	pDC-> FillSolidRect(&rect,   RGB(255,255,255));*/
	return TRUE;
	//return CButton::OnEraseBkgnd(pDC);
}
