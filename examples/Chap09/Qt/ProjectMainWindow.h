/**********************************************************************

  �ļ���: ProjectMainWindow.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef Project_MainWindow_H
#define Project_MainWindow_H

#include <QMainWindow>
#include "ui_ProjectMainWindow.h"
#include <vtkSmartPointer.h>

class vtkImageViewer2;
class vtkRenderer;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;

class ProjectMainWindow : public QMainWindow, public Ui::ProjectMainWindow
{
	Q_OBJECT

public:
	ProjectMainWindow();
	~ProjectMainWindow();

private slots:
	//��Ӧ��ͼ���ļ��Ĳۺ���
	void onOpenSlot();

	//��Ӧ����ƶ�����Ϣ��ʵʱ������ĵ�ǰλ��
	void updateCoords(vtkObject* obj);

private:
	vtkSmartPointer< vtkImageViewer2 >           m_pImageViewer;
	vtkSmartPointer< vtkRenderer >                   m_pRenderder;

	vtkEventQtSlotConnect* m_Connections;
};

#endif
