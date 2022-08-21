#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main(int argc, char *argv[]) {
  auto points = vtkSmartPointer<vtkPoints>::New();
  auto point_id1 = points->InsertNextPoint(1.0, 0.0, 0.0); // id: 0
  auto point_id2 = points->InsertNextPoint(0.0, 0.0, 1.0); // id: 1
  auto point_id3 = points->InsertNextPoint(0.0, 0.0, 0.0); // id: 2

  // vtkLine 继承自 vtkCell
  auto line0 = vtkSmartPointer<vtkLine>::New();
  line0->GetPointIds()->SetId(0, point_id1);
  line0->GetPointIds()->SetId(1, point_id2);

  auto line1 = vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0, point_id2);
  line1->GetPointIds()->SetId(1, point_id3);

  auto line2 = vtkSmartPointer<vtkLine>::New();
  line2->GetPointIds()->SetId(0, point_id3);
  line2->GetPointIds()->SetId(1, point_id1);

  auto lines = vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line0);
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(lines);

  auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName("triangle_lines.vtk");
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
