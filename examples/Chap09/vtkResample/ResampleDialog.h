/**********************************************************************

  �ļ���: ResampleDialog.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#pragma once

// CResampleDialog dialog

class CResampleDialog : public CDialog
{
	DECLARE_DYNAMIC(CResampleDialog)

public:
	CResampleDialog(CWnd* pParent = NULL);   // standard constructor
	CResampleDialog(int dx, int dy, int dz, float sx, float sy, float sz, CWnd* pParent = NULL); 
	virtual ~CResampleDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_RESAMPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();


	afx_msg void OnEnChangeEditDx();
	afx_msg void OnEnChangeEditSx();
	afx_msg void OnEnChangeEditDy();
	afx_msg void OnEnChangeEditSy();
	afx_msg void OnEnChangeEditDz();
	afx_msg void OnEnChangeEditSz();

	afx_msg void OnBnClickedRadioDimension();
	afx_msg void OnBnClickedRadioSpace();

	void UpdateControl();

public:
	int   m_iDx, m_iDy, m_iDz;
	float m_fSx, m_fSy, m_fSz;

	bool  m_bChangeDim;
	bool  m_bChangeSpace;
	
	
};
