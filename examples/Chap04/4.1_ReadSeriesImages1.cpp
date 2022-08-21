/**********************************************************************

  �ļ���: 4.1_ReadSeriesImages1.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkStringArray.h>
#include <vtkRenderWindow.h>


int main()
{
	//����ͼ�����е��ļ�������
	vtkSmartPointer< vtkStringArray > fileArray = vtkSmartPointer< vtkStringArray >::New();
	char fileName[128];
	for(int i = 1; i < 100; i++)
	{
		sprintf(fileName, "../data/Head/head%03d.jpg", i);
		vtkstd::string fileStr(fileName);
		fileArray->InsertNextValue(fileStr);	
	}

	//��ȡJPG����ͼ��
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileNames(fileArray);

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	//��ʾ��ȡ��JPGͼ��
	vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetInteractorStyle(style);

	imageViewer->SetSlice(50); //Ĭ����ʾ��50����Ƭ(����50��)
	imageViewer->SetSliceOrientationToXY();
	//imageViewer->SetSliceOrientationToYZ();
	//imageViewer->SetSliceOrientationToXZ();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ReadSeriesImages1");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}