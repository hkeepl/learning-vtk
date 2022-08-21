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

  // 设置相机
  auto camera = vtkSmartPointer<vtkCamera>::New();
  camera->SetClippingRange(0.0475, 2.3786);
  camera->SetFocalPoint(0.0573, -0.2134, -0.0523);
  camera->SetPosition(0.3245, -0.1139, -0.2932);
  camera->SetViewUp(-0.2234, 0.9983, 0.0345);
  renderer->SetActiveCamera(camera);

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