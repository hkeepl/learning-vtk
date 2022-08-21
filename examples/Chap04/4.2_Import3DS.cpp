/**********************************************************************

  �ļ���: 4.2_Import3DS.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtk3DSImporter.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

//�����ļ���data/R8.3ds
int main ( int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Required arguments: Filename(*.3ds)" << std::endl;
		return EXIT_FAILURE;
	}

	std::string filename = argv[1];
	std::cout << "Reading " << filename << std::endl;

	// 3DS Import
	vtkSmartPointer<vtk3DSImporter> importer = vtkSmartPointer<vtk3DSImporter>::New();
	importer->SetFileName ( filename.c_str() );
	importer->ComputeNormalsOn();
	importer->Read();

	vtkSmartPointer<vtkRenderer> renderer = importer->GetRenderer();
	vtkSmartPointer<vtkRenderWindow> renderWindow = importer->GetRenderWindow();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->GradientBackgroundOn();
	renderer->SetBackground(1.0, 1.0, 1.0);
	renderer->SetBackground2(0.0, 0.0, 0.0);
	renderWindow->Render();
	renderWindow->SetSize(640, 480);
	renderWindow->SetWindowName("Import3DS");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}