/**********************************************************************

  �ļ���: vtkView3D.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#pragma once

#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
// CvtkView3D

class CvtkView3D : public CStatic
{
	DECLARE_DYNAMIC(CvtkView3D)

public:
	CvtkView3D();
	virtual ~CvtkView3D();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();

public:
	afx_msg void OnPaint();
	void Render();

	vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() {return m_RenderWindow->GetInteractor();}
	vtkSmartPointer<vtkRenderer> GetRenderer() {return m_Renderer;}


public:
	vtkSmartPointer<vtkRenderer>     m_Renderer;
	vtkSmartPointer<vtkRenderWindow> m_RenderWindow;
};


