/**********************************************************************

  �ļ���: 5.3_GetImageInformationExample.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>

//����ͼ��../data/lena.bmp
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.bmp)"<<std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName ( argv[1] );
	reader->Update();

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);
	std::cout<<"ͼ��ά��:" <<dims[0]<<" "<<dims[1]<<" "<<dims[2]<<std::endl;

	double origin[3];
	reader->GetOutput()->GetOrigin(origin);
	std::cout<<"ͼ��ԭ��:" <<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;

	double spaceing[3];
	reader->GetOutput()->GetSpacing(spaceing);
	std::cout<<"���ؼ��:" <<spaceing[0]<<" "<<spaceing[1]<<" "<<spaceing[2]<<std::endl;

	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("GetImageInformationExample");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
