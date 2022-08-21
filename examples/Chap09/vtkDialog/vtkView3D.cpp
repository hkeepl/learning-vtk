/**********************************************************************

  �ļ���: vtkView3D.cpp 
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

// vtkView3D.cpp : implementation file
//

#include "stdafx.h"
#include "vtkDialog.h"
#include "vtkView3D.h"


// CvtkView3D

IMPLEMENT_DYNAMIC(CvtkView3D, CStatic)

CvtkView3D::CvtkView3D()
{

}

CvtkView3D::~CvtkView3D()
{
}


BEGIN_MESSAGE_MAP(CvtkView3D, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CvtkView3D message handlers



void CvtkView3D::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
}

void CvtkView3D::Render()
{
	m_Renderer->ResetCamera();
	m_RenderWindow->Render();
}

void CvtkView3D::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CRect rect;
	GetClientRect(rect);

	m_Renderer = vtkSmartPointer<vtkRenderer>::New();

	m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	m_RenderWindow->SetParentId(this->m_hWnd);
	m_RenderWindow->SetSize(rect.Width(), rect.Height());
	m_RenderWindow->AddRenderer(m_Renderer);

	if(m_RenderWindow->GetInteractor() == NULL)
	{
		vtkSmartPointer<vtkRenderWindowInteractor> RenderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		RenderWindowInteractor->SetRenderWindow(m_RenderWindow);
		RenderWindowInteractor->Initialize();
	}

	CStatic::PreSubclassWindow();
}
