/**********************************************************************

  �ļ���: 3.2_TrianglePoints.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>

int main(int argc, char *argv[])
{
	//����������
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint ( 1.0, 0.0, 0.0 );
	points->InsertNextPoint ( 0.0, 0.0, 0.0 );
	points->InsertNextPoint ( 0.0, 1.0, 0.0 );

	//����vtkPolyData���͵����ݣ�vtkPolyData������vtkPointSet��
	//vtkPointSet��vtkDataSet�����ࡣ
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

	//�������ĵ����ݼ��뵽vtkPolyData������
	polydata->SetPoints ( points );

	//��vtkPolyData���͵�����д�뵽һ��vtk�ļ�������λ���ǹ��̵�ǰĿ¼
	vtkSmartPointer< vtkPolyDataWriter > writer = vtkSmartPointer< vtkPolyDataWriter >::New();
	writer->SetFileName("triangle.vtk");
	writer->SetInput(polydata);
	writer->Write();

	return EXIT_SUCCESS;
}
