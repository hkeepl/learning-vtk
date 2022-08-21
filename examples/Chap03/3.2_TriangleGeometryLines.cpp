/**********************************************************************

  �ļ���: 3.2_TriangleGeometryLines.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>

int main(int argc, char *argv[])
{
	//�������������
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint ( 1.0, 0.0, 0.0 ); //���ص�һ�����ID��0
	points->InsertNextPoint ( 0.0, 0.0, 1.0 ); //���صڶ������ID��1
	points->InsertNextPoint ( 0.0, 0.0, 0.0 ); //���ص��������ID��2

	//ÿ���������֮��ֱ𴴽�һ����
	//SetId()�ĵ�һ���������߶εĶ˵�ID���ڶ������������ӵĵ��ID
	vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
	line0->GetPointIds()->SetId ( 0,0 ); 
	line0->GetPointIds()->SetId ( 1,1 );

	vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
	line1->GetPointIds()->SetId ( 0,1 );
	line1->GetPointIds()->SetId ( 1,2 );

	vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
	line2->GetPointIds()->SetId ( 0,2 );
	line2->GetPointIds()->SetId ( 1,0 );

	//����Cell���飬���ڴ洢���ϴ������߶�
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	lines->InsertNextCell ( line0 );
	lines->InsertNextCell ( line1 );
	lines->InsertNextCell ( line2 );

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

	//������߼��뵽���ݼ��У�ǰ��ָ�����ݼ��ļ��Σ�����ָ��������
	polydata->SetPoints ( points );
	polydata->SetLines ( lines );

	vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
	writer->SetFileName ( "TriangleLines.vtk" );
	writer->SetInput ( polydata );
	writer->Write();

	return EXIT_SUCCESS;
}