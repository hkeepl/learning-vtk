/**********************************************************************

  �ļ���: MainWindow.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include <vtkSmartPointer.h>

class vtkWin32RenderWindowInteractor;
class vtkRenderer;
class vtkRenderWindow;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;
class vtkViewImage2D;
class vtkViewImage3D;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

private slots:
	//��ͼ���ļ��Ĳۺ���
	void onOpenSlot();

private:
    //��ʼ��
    void initViews();

    void setupConnection();

	vtkSmartPointer< vtkRenderer >                           m_AxialRenderder;
	vtkSmartPointer< vtkRenderer >                           m_SagittalRenderder;
	vtkSmartPointer< vtkRenderer >                           m_CoronalRenderder;
	vtkSmartPointer< vtkRenderer >                           m_3DRenderder;

    vtkSmartPointer< vtkRenderWindow >                 m_AxialRenWin;
    vtkSmartPointer< vtkRenderWindow >                 m_SagittalRenWin;
	vtkSmartPointer< vtkRenderWindow >                 m_CoronalRenWin;
	vtkSmartPointer< vtkRenderWindow >                 m_3DRenWin;

	vtkSmartPointer< vtkRenderWindowInteractor >  m_AxialInteractor;
	vtkSmartPointer< vtkRenderWindowInteractor >  m_SagittalInteractor;
	vtkSmartPointer< vtkRenderWindowInteractor >  m_CoronalInteractor;
    vtkSmartPointer< vtkRenderWindowInteractor >  m_3DInteractor;

    vtkSmartPointer< vtkViewImage2D >           m_AxialImage;
    vtkSmartPointer< vtkViewImage2D >           m_SagittalImage;
    vtkSmartPointer< vtkViewImage2D >           m_CoronalImage;
    vtkSmartPointer< vtkViewImage3D >           m_3DImage;

	Ui_MainWindow *m_MainWindow; 
};

#endif
