/**********************************************************************

  �ļ���: 3.2_TriangleVertices.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkCellArray.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>

int main(int argc, char *argv[])
{
    //�����������
    double X[3] = {1.0, 0.0, 0.0};
    double Y[3] = {0.0, 0.0, 1.0};
    double Z[3] = {0.0, 0.0, 0.0};

    //�����������Լ���ÿ���������ϼ���(����)Vertex����Cell
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

    for ( unsigned int i = 0; i < 3; ++i )
    {
        //�������ڴ洢���������м������vtkIdType���൱��int��long��
        vtkIdType pid[1];

        //��ÿ����������뵽vtkPoints�У�InsertNextPoint()���ؼ���ĵ�������ţ�
        //����������Ҫʹ�����������������Vertex���͵�Cell
        pid[0] = points->InsertNextPoint ( X[i], Y[i], Z[i] );

        //��ÿ��������Ϸֱ𴴽�һ��Vertex��Vertex��Cell���һ��
        vertices->InsertNextCell ( 1,pid );
    }

    //����vtkPolyData����
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //ָ�����ݼ��ļ���(��pointsָ��)���Լ����ݼ�������(��verticesָ��)
    polydata->SetPoints ( points );
    polydata->SetVerts ( vertices );

    //�����ɵ����ݼ�д��TriangleVerts.vtk�ļ�������ڹ��̵�ǰĿ¼��
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName ( "TriangleVerts.vtk" );
    writer->SetInput ( polydata );
    writer->Write();

    return EXIT_SUCCESS;
}