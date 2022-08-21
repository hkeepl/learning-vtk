/**********************************************************************

  �ļ���: ProjectMainWindow.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include "ProjectMainWindow.h"
#include <QFileDialog>
#include <QDir>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <QVTKWidget.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkCommand.h>

ProjectMainWindow::ProjectMainWindow()
{
	setupUi(this);

	m_pImageViewer  = vtkSmartPointer< vtkImageViewer2 >::New();
	m_pRenderder      = vtkSmartPointer< vtkRenderer >::New();

	// ����m_QVTKWidget����Ⱦ��
	m_QVTKWidget->GetRenderWindow()->AddRenderer(m_pRenderder);

	//���Ӵ򿪵��ź�����Ӧ�Ĳ�
	connect( m_OpenAction, SIGNAL( triggered() ), this, SLOT( onOpenSlot() ) ); 

	m_Connections = vtkEventQtSlotConnect::New();
	m_Connections->Connect(m_QVTKWidget->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseMoveEvent,
		this,
		SLOT(updateCoords(vtkObject*)));
}

ProjectMainWindow::~ProjectMainWindow()
{
}

void ProjectMainWindow::onOpenSlot()
{
	QString filter;
	filter = "JPEG image file (*.jpg *.jpeg)";

	QDir dir;
	QString fileName = QFileDialog::getOpenFileName( this, QString(tr("��ͼ��")), dir.absolutePath() , filter );
	if ( fileName.isEmpty() == true ) return;

	// ֧�ִ�����·���Ķ�ȡ
	QByteArray ba = fileName.toLocal8Bit();
	const char *fileName_str = ba.data();

	// ��vtkJPEGReader��ȡJPGͼ��
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(fileName_str);

	// ��reader�������Ϊm_pImageViewer�����룬������m_pImageViewer����Ⱦ��m_pRenderer�Ĺ���
	m_pImageViewer->SetInput(reader->GetOutput());
	m_pImageViewer->UpdateDisplayExtent();
	m_pImageViewer->SetRenderWindow(m_QVTKWidget->GetRenderWindow());
	m_pImageViewer->SetRenderer(m_pRenderder);
	m_pImageViewer->SetupInteractor(m_QVTKWidget->GetRenderWindow()->GetInteractor());
	m_pImageViewer->SetSliceOrientationToXY(); //Ĭ�Ͼ�����������
	m_pImageViewer->GetImageActor()->InterpolateOff();
	m_pRenderder->ResetCamera();
	m_pRenderder->DrawOn();
	m_QVTKWidget->GetRenderWindow()->Render();
}

void ProjectMainWindow::updateCoords(vtkObject* obj)
{
	// ��ȡ������
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);

	// ��ȡ���ĵ�ǰλ��
	int event_pos[2];
	iren->GetEventPosition(event_pos);

	QString str;
	str.sprintf("x=%d : y=%d", event_pos[0], event_pos[1]);
	m_StatusBar->showMessage(str);
}
