#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main() {
  auto cone = vtkSmartPointer<vtkConeSource>::New();
  auto cube = vtkSmartPointer<vtkCubeSource>::New();
  auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  auto sphere = vtkSmartPointer<vtkSphereSource>::New();

  auto cone_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cone_mapper->SetInputConnection(cone->GetOutputPort());
  auto cube_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cube_mapper->SetInputConnection(cube->GetOutputPort());
  auto cylinder_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinder_mapper->SetInputConnection(cylinder->GetOutputPort());
  auto sphere_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  sphere_mapper->SetInputConnection(sphere->GetOutputPort());

  auto cone_actor = vtkSmartPointer<vtkActor>::New();
  cone_actor->SetMapper(cone_mapper);
  auto cube_actor = vtkSmartPointer<vtkActor>::New();
  cube_actor->SetMapper(cube_mapper);
  auto cylinder_actor = vtkSmartPointer<vtkActor>::New();
  cylinder_actor->SetMapper(cylinder_mapper);
  auto sphere_actor = vtkSmartPointer<vtkActor>::New();
  sphere_actor->SetMapper(sphere_mapper);

  auto renderer1 = vtkSmartPointer<vtkRenderer>::New();
  renderer1->AddActor(cone_actor);
  renderer1->SetViewport(0.0, 0.0, 0.5, 0.5);
  renderer1->SetBackground(1.0, 0.0, 0.0);
  auto renderer2 = vtkSmartPointer<vtkRenderer>::New();
  renderer2->AddActor(cube_actor);
  renderer2->SetViewport(0.5, 0.0, 1.0, 0.5);
  renderer2->SetBackground(0.0, 1.0, 0.0);
  auto renderer3 = vtkSmartPointer<vtkRenderer>::New();
  renderer3->AddActor(cylinder_actor);
  renderer3->SetViewport(0.0, 0.5, 0.5, 1.0);
  renderer3->SetBackground(0.0, 0.0, 1.0);
  auto renderer4 = vtkSmartPointer<vtkRenderer>::New();
  renderer4->AddActor(sphere_actor);
  renderer4->SetViewport(0.5, 0.5, 1.0, 1.0);
  renderer4->SetBackground(1.0, 1.0, 0.0);

  auto ren_win = vtkSmartPointer<vtkRenderWindow>::New();
  ren_win->AddRenderer(renderer1);
  ren_win->AddRenderer(renderer2);
  ren_win->AddRenderer(renderer3);
  ren_win->AddRenderer(renderer4);
  ren_win->SetSize(640, 480);
  ren_win->SetWindowName("Viewport");

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(ren_win);
  interactor->Initialize();
  interactor->Start();

  return 0;
}