/**********************************************************************

  �ļ���: 6.7_PolyDataConstrainedDelaunay2D.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>

int main(int, char *[])
{
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();

	unsigned int gridSize = 10;
	for(unsigned int x = 0; x < gridSize; x++)
	{
		for(unsigned int y = 0; y < gridSize; y++)
		{
			points->InsertNextPoint(x, y, vtkMath::Random(0.0, 3.0));
		}
	}

	vtkSmartPointer<vtkPolyData> polydata =
		vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	vtkSmartPointer<vtkPolygon> poly =
		vtkSmartPointer<vtkPolygon>::New();
	/*poly->GetPointIds()->InsertNextId(22);
	poly->GetPointIds()->InsertNextId(23);
	poly->GetPointIds()->InsertNextId(24);
	poly->GetPointIds()->InsertNextId(25);
	poly->GetPointIds()->InsertNextId(35);
	poly->GetPointIds()->InsertNextId(45);
	poly->GetPointIds()->InsertNextId(44);
	poly->GetPointIds()->InsertNextId(43);
	poly->GetPointIds()->InsertNextId(42);
	poly->GetPointIds()->InsertNextId(32);*/

	poly->GetPointIds()->InsertNextId(32);
	poly->GetPointIds()->InsertNextId(42);
	poly->GetPointIds()->InsertNextId(43);
	poly->GetPointIds()->InsertNextId(44);
	poly->GetPointIds()->InsertNextId(45);
	poly->GetPointIds()->InsertNextId(35);
	poly->GetPointIds()->InsertNextId(25);
	poly->GetPointIds()->InsertNextId(24);
	poly->GetPointIds()->InsertNextId(23);
	poly->GetPointIds()->InsertNextId(22);

	vtkSmartPointer<vtkCellArray> cell =
		vtkSmartPointer<vtkCellArray>::New();
	cell->InsertNextCell(poly);

	vtkSmartPointer<vtkPolyData> boundary =
		vtkSmartPointer<vtkPolyData>::New();
	boundary->SetPoints(points);
	boundary->SetPolys(cell);

	vtkSmartPointer<vtkDelaunay2D> delaunay =
		vtkSmartPointer<vtkDelaunay2D>::New();
	delaunay->SetInput(polydata);
	delaunay->SetSource(boundary);
	delaunay->Update();

	vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	glyphFilter->SetInput(polydata);
	glyphFilter->Update();

	vtkSmartPointer<vtkPolyDataMapper> pointsMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	pointsMapper->SetInput(glyphFilter->GetOutput());

	vtkSmartPointer<vtkActor> pointsActor =
		vtkSmartPointer<vtkActor>::New();
	pointsActor->SetMapper(pointsMapper);
	pointsActor->GetProperty()->SetPointSize(3);
	pointsActor->GetProperty()->SetColor(1,0,0);

	vtkSmartPointer<vtkPolyDataMapper> triangulatedMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	triangulatedMapper->SetInput(delaunay->GetOutput());

	vtkSmartPointer<vtkActor> triangulatedActor =
		vtkSmartPointer<vtkActor>::New();
	triangulatedActor->SetMapper(triangulatedMapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(pointsActor);
	renderer->AddActor(triangulatedActor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataConstrainedDelaunay2D");
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}