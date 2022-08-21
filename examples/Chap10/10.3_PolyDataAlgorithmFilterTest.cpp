/**********************************************************************

  �ļ���: 10.3_PolyDataAlgorithmFilterTest.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include "vtkPolyDataAlgorithmFilter.h"

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkPoints> points1 =
		vtkSmartPointer<vtkPoints>::New();
	points1->InsertNextPoint(1.0, 2.0, 3.0);
	vtkSmartPointer<vtkPolyData> inputPolydata1 =
		vtkSmartPointer<vtkPolyData>::New();
	inputPolydata1->SetPoints(points1);

	vtkSmartPointer<vtkPoints> points2 =
		vtkSmartPointer<vtkPoints>::New();
	points2->InsertNextPoint(4.0, 5.0, 6.0);
	points2->InsertNextPoint(4.0, 5.0, 6.0);
	vtkSmartPointer<vtkPolyData> inputPolydata2 =
		vtkSmartPointer<vtkPolyData>::New();
	inputPolydata2->SetPoints(points2);

	vtkSmartPointer<vtkPolyDataAlgorithmFilter> filter =
		vtkSmartPointer<vtkPolyDataAlgorithmFilter>::New();
	filter->AddInputConnection(inputPolydata1->GetProducerPort());
	filter->AddInputConnection(inputPolydata2->GetProducerPort());
	filter->DebugOn();

	filter->Update();

	vtkPolyData* outputPolydata = filter->GetOutput();

	std::cout << "Output points: " << outputPolydata->GetNumberOfPoints() << std::endl;
	system("pause");

	return EXIT_SUCCESS;
}