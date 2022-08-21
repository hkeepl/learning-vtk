/**********************************************************************

  �ļ���: GradientColorButton.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#if !defined(AFX_GRADIENTCOLORBUTTON_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_)
#define AFX_GRADIENTCOLORBUTTON_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GradientColorButton.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CGradientColorButton window
#include <Afxtempl.h>

#include "ValueColorTable.h"

#define WM_UPDATE_COLOR_INFO_MSG WM_USER+100
#define WM_UPDATE_COLOR_VIEW_MSG WM_USER+101

class  CGradientColorButton : public CButton
{
// Construction
public:
	CGradientColorButton();
	//����ֵ����ɫ��
	void SetValueColorTable(CValueColorTable &ValueColorTable);
	//��ȡֵ����ɫ��
	void GetValueColorTable(CValueColorTable &ValueColorTable);
	void GetValueColorTable(std::vector<std::vector<double>>& table);
	void SetTableByValueMinMax(double min, double max);
	bool GetCurrentValueColor(double& value, double& r, double& g, double& b);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradientColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGradientColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGradientColorButton)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	//���ݲ�ֵ�ռ�ĳ���Length��ƫ����offest������ɫ
	long   CalculateColor(double Length,double offset);
	long   CalculateDiscreteColor(double Length,double offset);
	int    GetSelectedColorIndex(const CPoint point);
	double GetPointValue(const CPoint point);

	void   DrawContinusColorTable(CDC *pDC, CRect &Rc);
	void   DrawDiscreteColorTable(CDC *pDC, CRect &Rc);

	//ֵ����ɫ��
	CValueColorTable m_ValueColorTable; 
	//��갴��ʱ���ؼ��������
	int  m_ValueColorIndex;				 
	//�ж��������Ƿ���	
	bool m_IsLButtonDown;

	CDC MemDC; //���ȶ���һ����ʾ�豸����
	CBitmap MemBitmap;//����һ��λͼ����

	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADIENTCOLORBUTTON_H__B571195B_38A2_46E2_B99F_C8E23142A5FC__INCLUDED_)
