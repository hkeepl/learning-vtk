/**********************************************************************

  �ļ���: 8.1_ObserverCommandDemo1.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCallbackCommand.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

long pressCounts = 0;

//��һ��������ص�������ע��ص�������ǩ�������ܸ��ġ�
void MyCallbackFunc(vtkObject*, unsigned long eid, void* clientdata, void *calldata)
{
	std::cout<<"You have clicked: "<<++pressCounts<<" times."<<std::endl;
}

//����ͼ��../data/VTK-logo.png
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.png)"<<std::endl;
		return 0;
	}

	vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
	reader->SetFileName(argv[1]);

	vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
	viewer->SetInput(reader->GetOutput());

	vtkSmartPointer<vtkRenderWindowInteractor> interactor =  vtkSmartPointer<vtkRenderWindowInteractor>::New();
	viewer->SetupInteractor(interactor);
	viewer->Render();

	viewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	viewer->SetSize(640, 480);
	viewer->GetRenderWindow()->SetWindowName("ObserverCommandDemo1");

	//�ڶ��������ûص�������
	vtkSmartPointer<vtkCallbackCommand> mouseCallback = 
		vtkSmartPointer<vtkCallbackCommand>::New();
	mouseCallback->SetCallback ( MyCallbackFunc );

	//����������vtkCallbackCommand������ӵ��۲����б�
	interactor->SetRenderWindow(viewer->GetRenderWindow());
	interactor->AddObserver(vtkCommand::LeftButtonPressEvent, mouseCallback);

	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}