/**********************************************************************

  �ļ���: 5.3_ImageShrinkMagnifyExample.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkBMPReader.h>
#include <vtkImageShrink3D.h>
#include <vtkImageMagnify.h>

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

	vtkSmartPointer<vtkImageShrink3D> shrinkFilter = 
		vtkSmartPointer<vtkImageShrink3D>::New();
	shrinkFilter->SetInputConnection(reader->GetOutputPort());
	shrinkFilter->SetShrinkFactors(16,16,1);
	shrinkFilter->Update();

	vtkSmartPointer<vtkImageMagnify> magnifyFilter =
		vtkSmartPointer<vtkImageMagnify>::New();
	magnifyFilter->SetInputConnection(reader->GetOutputPort());
	magnifyFilter->SetMagnificationFactors(10,10,1);
	magnifyFilter->Update();

	int originalDims[3];
	reader->GetOutput()->GetDimensions(originalDims);

	double originalSpace[3];
	reader->GetOutput()->GetSpacing(originalSpace);

	int shrinkDims[3];
	shrinkFilter->GetOutput()->GetDimensions(shrinkDims);

	double shrinkSpace[3];
	shrinkFilter->GetOutput()->GetSpacing(shrinkSpace);

	int magnifyDims[3];
	magnifyFilter->GetOutput()->GetDimensions(magnifyDims);

	double magnifySpace[3];
	magnifyFilter->GetOutput()->GetSpacing(magnifySpace);

	std::cout<<"ԭͼͼ��ά��      ��"<<originalDims[0] << " "<<originalDims[1]<<" "<<originalDims[2]<<std::endl;
	std::cout<<"ԭͼͼ�����ؼ��  ��"<<originalSpace[0] << " "<<originalSpace[1]<<" "<<originalSpace[2]<<std::endl;
	std::cout<<"������ͼ��ά��    ��"<<shrinkDims[0] << " "<<shrinkDims[1]<<" "<<shrinkDims[2]<<std::endl;
	std::cout<<"������ͼ�����ؼ����"<<shrinkSpace[0] << " "<<shrinkSpace[1]<<" "<<shrinkSpace[2]<<std::endl;
	std::cout<<"������ͼ��ά��    ��"<<magnifyDims[0] << " "<<magnifyDims[1]<<" "<<magnifyDims[2]<<std::endl;
	std::cout<<"������ͼ�����ؼ����"<<magnifySpace[0] << " "<<magnifySpace[1]<<" "<<magnifySpace[2]<<std::endl;

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInput(
		reader->GetOutput());

	vtkSmartPointer<vtkImageActor> shrinkActor =
		vtkSmartPointer<vtkImageActor>::New();
	shrinkActor->SetInput(shrinkFilter->GetOutput());

	vtkSmartPointer<vtkImageActor> magnifyActor =
		vtkSmartPointer<vtkImageActor>::New();
	magnifyActor->SetInput(magnifyFilter->GetOutput());

	double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
	double shrinkViewport[4] = {0.33, 0.0, 0.66, 1.0};
	double magnifyViewport[4] = {0.66, 0.0, 1.0, 1.0};

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(originalViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> shrinkRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	shrinkRenderer->SetViewport(shrinkViewport);
	shrinkRenderer->AddActor(shrinkActor);
	shrinkRenderer->ResetCamera();
	shrinkRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> magnifyRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	magnifyRenderer->SetViewport(magnifyViewport);
	magnifyRenderer->AddActor(magnifyActor);
	magnifyRenderer->ResetCamera();
	magnifyRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(shrinkRenderer);
	renderWindow->AddRenderer(magnifyRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("ImageShrinkMagnifyExample");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();

	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
