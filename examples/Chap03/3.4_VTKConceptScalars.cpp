/**********************************************************************

  �ļ���: 3.4_VTKConceptScalars.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
	//�����㼯���ݣ�������������㡣
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0,0,0);
	points->InsertNextPoint(1,0,0);

	//������������ݡ�
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	//׼����������ݵı���ֵ����������ֵ�ֱ�Ϊ1��2��
	vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
	weights->SetNumberOfValues(2);
	weights->SetValue(0, 1);
	weights->SetValue(1, 2);

	//�Ȼ�ȡ��������ݵĵ�����ָ�룬Ȼ�����øõ����ݵı�������ֵ��
	polydata->GetPointData()->SetScalars(weights);

	//���������Ϊ0�ĵ�ı���ֵ��
	double weight = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
	std::cout << "double weight: " << weight << std::endl;

	return EXIT_SUCCESS;
}