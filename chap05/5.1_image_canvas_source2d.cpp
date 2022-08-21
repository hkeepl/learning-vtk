#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkImageMapper.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main() {
  auto canvas = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  canvas->SetScalarTypeToUnsignedChar();
  canvas->SetNumberOfScalarComponents(1);
  canvas->SetExtent(0, 100, 0, 100, 0, 0);
  canvas->SetDrawColor(127, 0, 0, 0);
  canvas->FillBox(0, 100, 0, 100);
  canvas->SetDrawColor(255, 0, 0, 0);
  canvas->FillBox(20, 40, 20, 60);
  canvas->Update();

  // Create actor
  // vtkImageData直接传给vtkImageActor
  auto actor = vtkSmartPointer<vtkImageActor>::New();
  actor->SetInputData(canvas->GetOutput());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetViewport(0, 0, 0.5, 0.5);
  renderer->AddActor(actor);
  renderer->ResetCamera();
  renderer->SetBackground(0, 1, 0);

  auto ellipsoid = vtkSmartPointer<vtkImageEllipsoidSource>::New();
  ellipsoid->SetWholeExtent(canvas->GetOutput()->GetExtent());
  ellipsoid->SetOutputScalarTypeToUnsignedChar();
  ellipsoid->SetInValue(0);
  ellipsoid->SetOutValue(127);
  ellipsoid->SetCenter(50, 50, 0);
  ellipsoid->SetRadius(36, 19, 1);
  ellipsoid->Update();
  auto actor2 = vtkSmartPointer<vtkImageActor>::New();
  actor2->SetInputData(ellipsoid->GetOutput());
  auto renderer2 = vtkSmartPointer<vtkRenderer>::New();
  renderer2->SetViewport(0.5, 0.5, 1, 1);
  renderer2->AddActor(actor2);
  renderer2->ResetCamera();
  renderer2->SetBackground(0, 0, 1);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->AddRenderer(renderer2);
  render_win->SetSize(640, 480);
  render_win->Render();
  render_win->SetWindowName("ImageCanvasSource2D");

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->SetRenderWindow(render_win);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
