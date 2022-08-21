/**********************************************************************

  �ļ���: 4.1_ReadSeriesImages3.cpp
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
#include <vtkImageAppend.h>
#include <vtkRenderWindow.h>


int main()
{
	vtkSmartPointer<vtkImageAppend > append = vtkSmartPointer<vtkImageAppend >::New();
	append->SetAppendAxis(2);

	vtkSmartPointer<vtkJPEGReader>reader =
		vtkSmartPointer<vtkJPEGReader>::New();
	char fileName[128];
	for(int i = 1; i < 21; i++)
	{
		sprintf(fileName,"../data/Head/head%03d.jpg", i);
		reader->SetFileName(fileName);
		append->AddInputConnection(reader->GetOutputPort());
	}

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

	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ReadSeriesImages3");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}