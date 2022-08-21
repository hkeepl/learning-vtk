/**********************************************************************

  �ļ���: 4.1_ReadSeriesImages2.cpp
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
	vtkSmartPointer<vtkJPEGReader>reader =  
		vtkSmartPointer<vtkJPEGReader>::New();  
	reader->SetFilePrefix ("../data/Head/head");  
	reader->SetFilePattern("%s%03d.jpg");  
	reader ->SetDataExtent (0,255,0,255,1,100);
	reader->Update();  

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
	imageViewer->GetRenderWindow()->SetWindowName("ReadSeriesImages2");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}