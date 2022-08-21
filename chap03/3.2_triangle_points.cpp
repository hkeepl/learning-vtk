#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[]) {
  auto points = vtkSmartPointer<vtkPoints>::New();
  auto point_id1 = points->InsertNextPoint(1.0, 0.0, 0.0); // id: 0
  auto point_id2 = points->InsertNextPoint(0.0, 0.0, 1.0); // id: 1
  auto point_id3 = points->InsertNextPoint(0.0, 0.0, 0.0); // id: 2

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName("triangle.vtk");
  writer->SetInputData(polydata);
  writer->Write();

  /* Show polydata */

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polydata);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(render_win);
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
