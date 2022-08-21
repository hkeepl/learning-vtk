/**********************************************************************

  �ļ���: 5.3_ImageChangeInformationExample.cpp
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
#include <vtkBMPReader.h>
#include <vtkImageChangeInformation.h>
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
	reader->SetFileName(argv[1]);
	reader->Update();

	int dims[3];
	double origin[3];
	double spaceing[3];

	reader->GetOutput()->GetDimensions(dims);
	std::cout<<"ԭͼ��ά��:" <<dims[0]<<" "<<dims[1]<<" "<<dims[2]<<std::endl;
	reader->GetOutput()->GetOrigin(origin);
	std::cout<<"ԭͼ��ԭ��:" <<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
	reader->GetOutput()->GetSpacing(spaceing);
	std::cout<<"ԭ���ؼ��:" <<spaceing[0]<<" "<<spaceing[1]<<" "<<spaceing[2]<<std::endl<<std::endl;;

	vtkSmartPointer<vtkImageChangeInformation> changer =
		vtkSmartPointer<vtkImageChangeInformation>::New();
	changer->SetInput(reader->GetOutput());
	changer->SetOutputOrigin(100, 100, 0);
	changer->SetOutputSpacing(5,5,1);
	changer->SetCenterImage(1);
	changer->Update();

	changer->GetOutput()->GetDimensions(dims);
	std::cout<<"�޸ĺ�ͼ��ά��:" <<dims[0]<<" "<<dims[1]<<" "<<dims[2]<<std::endl;
	changer->GetOutput()->GetOrigin(origin);
	std::cout<<"�޸ĺ�ͼ��ԭ��:" <<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
	changer->GetOutput()->GetSpacing(spaceing);
	std::cout<<"�޸ĺ����ؼ��:" <<spaceing[0]<<" "<<spaceing[1]<<" "<<spaceing[2]<<std::endl;

	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(changer->GetOutputPort());
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ImageChangeInformationExample");


	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
