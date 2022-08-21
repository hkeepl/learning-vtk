#include <iostream>

#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main()
{
  std::cout << "2.2_RenderCylinder Lights" << std::endl;
  auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(3.0);
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  // 添加灯光
  auto light = vtkSmartPointer<vtkLight>::New();
  light->SetColor(0, 1, 0);
  light->SetPosition(0, 1, 0);
  light->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
  renderer->AddLight(light);

  auto light2 = vtkSmartPointer<vtkLight>::New();
  light2->SetColor(0, 0, 1);
  light2->SetPosition(0, -1, 0);
  light2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
  renderer->AddLight(light2);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->SetSize(420, 128);

  auto render_win_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  render_win_interactor->SetRenderWindow(render_win);

  auto istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  render_win_interactor->SetInteractorStyle(istyle);

  render_win_interactor->Initialize();
  render_win_interactor->Start();

  return 0;
}