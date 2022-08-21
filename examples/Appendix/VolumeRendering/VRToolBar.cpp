/**********************************************************************

  �ļ���: VRToolBar.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

// VRToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "VRApp.h"
#include "VRToolBar.h"
#include "VRAppDoc.h"
#include "MainFrm.h"

// CVRToolBar dialog

IMPLEMENT_DYNAMIC(CVRToolBar, CDialogBar)

CVRToolBar::CVRToolBar(CWnd* pParent /*=NULL*/)
{

}

CVRToolBar::~CVRToolBar()
{
}

void CVRToolBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_VOLUME_COLOR,   m_VolumeColor);
	DDX_Control(pDX, IDC_VOLUME_OPACITY, m_VolumeOpacity);
}


BEGIN_MESSAGE_MAP(CVRToolBar, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, &OnInitDialog )
	ON_UPDATE_COMMAND_UI(IDC_VOLUME_COLOR, OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_VOLUME_OPACITY, OnUpdateButton)
	ON_EN_CHANGE(IDC_OPACITY_VALUE, &CVRToolBar::OnEnChangeOpacityValue)
END_MESSAGE_MAP()


// CVRToolBar message handlers
/*LONG*/LRESULT CVRToolBar::OnInitDialog ( /*UINT*/WPARAM  wParam, /*LONG*/LPARAM  lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);

	if (!UpdateData(FALSE))
	{
		TRACE0("Warning: UpdateData failed during dialog init.\n");
	}
	
	return bRet;
}

void CVRToolBar::OnUpdateButton(CCmdUI * pCmdUI){
	pCmdUI -> Enable(TRUE);
}

//���¿ؼ�
void CVRToolBar::InitControls()
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	CVRAppDoc *pDoc = (CVRAppDoc *)(pMainFrame->GetActiveDocument());

	m_VolumeOpacity.SetHistogram(pDoc->m_Min,pDoc->m_Max,pDoc->m_Histogram);
	m_VolumeColor.SetTableByValueMinMax(pDoc->m_Min,pDoc->m_Max);
}

void CVRToolBar::UpdateOpacityInfo(double gray, double opacity)
{
	CString strGray;
	strGray.Format("%.2f",gray);
	GetDlgItem(IDC_OPACITY_GRAY)->SetWindowText(strGray);

	CString strOpacity;
	strOpacity.Format("%.2f",opacity);
	GetDlgItem(IDC_OPACITY_VALUE)->SetWindowText(strOpacity);
}

void CVRToolBar::UpdateColorInfo(double gray)
{
	CString strGray;
	strGray.Format("%.2f",gray);
	GetDlgItem(IDC_COLOR_GRAY)->SetWindowText(strGray);
}

void CVRToolBar::OnEnChangeOpacityValue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogBar::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strGray;
	GetDlgItem(IDC_OPACITY_GRAY)->GetWindowText(strGray);

	CString strOpacity;
	GetDlgItem(IDC_OPACITY_VALUE)->GetWindowText(strOpacity);

	if(strGray.Compare("") == 0) return;

	double gray = atof(strGray);
	double opacity = atof(strOpacity);

	m_VolumeOpacity.SetKeyPoint(gray, opacity);
}
