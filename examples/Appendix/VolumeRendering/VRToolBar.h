/**********************************************************************

  �ļ���: VRToolBar.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#pragma once

#include "resource.h"
#include "TransparencySetButton.h"
#include "GradientColorButton.h"
// CVRToolBar dialog

class CVRToolBar : public CDialogBar
{
	DECLARE_DYNAMIC(CVRToolBar)

public:
	CVRToolBar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVRToolBar();

// Dialog Data
	enum { IDD = IDD_VR_TOOLBAR };

	//���¿ؼ�
	void InitControls();

	void UpdateOpacityInfo(double gray, double opacity);
	void UpdateColorInfo(double gray);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg /*LONG*/LRESULT OnInitDialog ( /*UINT*/WPARAM , /*LONG*/LPARAM  );
	afx_msg void OnUpdateButton(CCmdUI * pCmdUI); //��Ӧbutton��ť

	DECLARE_MESSAGE_MAP()

public:
	CGradientColorButton   m_VolumeColor;
	CTransparencySetButton m_VolumeOpacity;
	afx_msg void OnEnChangeOpacityValue();
};
