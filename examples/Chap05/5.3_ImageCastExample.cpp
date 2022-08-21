/**********************************************************************

  �ļ���: 5.3_ImageCastExample.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkBMPReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkMetaImageReader.h>
#include <vtkImageCast.h>
#include <vtkImageShiftScale.h>

//����ͼ��../data/brain.mhd
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.mhd)"<<std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkMetaImageReader> reader =
		vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	vtkSmartPointer<vtkImageCast> imageCast =
		vtkSmartPointer<vtkImageCast>::New();
	imageCast->SetInput((vtkDataObject *)reader->GetOutput());
	imageCast->SetOutputScalarTypeToFloat();

	vtkSmartPointer<vtkImageShiftScale> imageShiftScale =
		vtkSmartPointer<vtkImageShiftScale>::New();
	imageShiftScale->SetInput((vtkDataObject *)reader->GetOutput());
	imageShiftScale->SetOutputScalarTypeToFloat();

	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInput(imageCast->GetOutput());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);

	imageViewer->SetColorLevel(500);
	imageViewer->SetColorWindow(2000);
	imageViewer->SetSlice(40);
	imageViewer->SetSliceOrientationToXY();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ImageCastExample");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
