/**********************************************************************

  �ļ���: vtkView.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#pragma once

#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkImagePlaneWidget.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursor.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkImageData.h"

// CvtkView

class CvtkView : public CStatic
{
	DECLARE_DYNAMIC(CvtkView)

public:
	CvtkView();
	virtual ~CvtkView();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnPaint();

	void SetImageData(vtkSmartPointer<vtkImageData> ImageData);
	void SetupReslice();
	void SetSliceDirection(int dir) {m_Direction = dir;}
	void Render();

	vtkSmartPointer< vtkImagePlaneWidget > GetImagePlaneWidget() {return m_ImagePlaneWidget;}
	vtkSmartPointer< vtkResliceCursorWidget >    GetResliceCursorWidget() {return m_ResliceCursorWidget;}

	vtkSmartPointer< vtkResliceCursor > GetResliceCursor() {return m_ResliceCursor;}
	void SetResliceCursor(vtkSmartPointer< vtkResliceCursor > cursor);

public:
	vtkSmartPointer<vtkRenderer>    m_Renderer;
	vtkSmartPointer<vtkRenderWindow> m_RenderWindow;

	vtkSmartPointer< vtkImagePlaneWidget >   m_ImagePlaneWidget;
	vtkSmartPointer< vtkResliceCursorWidget> m_ResliceCursorWidget;
	vtkSmartPointer< vtkResliceCursor >      m_ResliceCursor;
	vtkSmartPointer< vtkResliceCursorThickLineRepresentation > m_ResliceCursorRep;

	vtkSmartPointer<vtkImageData> m_ImageData;
	int m_Direction;
};


