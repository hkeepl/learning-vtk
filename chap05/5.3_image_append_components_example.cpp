#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkImageLuminance.h>
#include <vtkImageMapper3D.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageData.h>
#include <vtkImageAppendComponents.h>
#include <vtkImageCanvasSource2D.h>

int main(int argc, char *argv[]) {
  auto red_source = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  red_source->SetNumberOfScalarComponents(1);
  red_source->SetScalarTypeToUnsignedChar();
  red_source->SetExtent(0, 100, 0, 100, 0, 0);
  red_source->SetDrawColor(0.0);
  red_source->FillBox(0, 100, 0, 100);
  red_source->SetDrawColor(255);
  red_source->FillBox(20, 40, 20, 40);

  auto green_source = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  green_source->SetNumberOfScalarComponents(1);
  green_source->SetScalarTypeToUnsignedChar();
  green_source->SetExtent(0, 100, 0, 100, 0, 0);
  green_source->SetDrawColor(0.0);
  green_source->FillBox(0, 100, 0, 100);
  green_source->SetDrawColor(255);
  green_source->FillBox(30, 50, 30, 50);

  auto blue_source = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  blue_source->SetNumberOfScalarComponents(1);
  blue_source->SetScalarTypeToUnsignedChar();
  blue_source->SetExtent(0, 100, 0, 100, 0, 0);
  blue_source->SetDrawColor(0.0);
  blue_source->FillBox(0, 100, 0, 100);
  blue_source->SetDrawColor(255);
  blue_source->FillBox(40, 60, 40, 60);

  auto append_filter = vtkSmartPointer<vtkImageAppendComponents>::New();
  append_filter->AddInputConnection(red_source->GetOutputPort());
  append_filter->AddInputConnection(green_source->GetOutputPort());
  append_filter->AddInputConnection(blue_source->GetOutputPort());

  auto orignal_actor = vtkSmartPointer<vtkImageActor>::New();
  orignal_actor->GetMapper()->SetInputConnection(append_filter->GetOutputPort());
  auto extract_red_filter_actor = vtkSmartPointer<vtkImageActor>::New();
  extract_red_filter_actor->GetMapper()->SetInputConnection(red_source->GetOutputPort());
  auto extract_green_filter_actor = vtkSmartPointer<vtkImageActor>::New();
  extract_green_filter_actor->GetMapper()->SetInputConnection(green_source->GetOutputPort());
  auto extract_blue_filter_actor = vtkSmartPointer<vtkImageActor>::New();
  extract_blue_filter_actor->GetMapper()->SetInputConnection(blue_source->GetOutputPort());

  auto original_renderer = vtkSmartPointer<vtkRenderer>::New();
  original_renderer->SetViewport(0, 0, 0.5, 0.5);
  original_renderer->AddActor(orignal_actor);
  original_renderer->ResetCamera();
  auto red_renderer = vtkSmartPointer<vtkRenderer>::New();
  red_renderer->SetViewport(0.5, 0, 1, 0.5);
  red_renderer->AddActor(extract_red_filter_actor);
  red_renderer->ResetCamera();
  auto green_renderer = vtkSmartPointer<vtkRenderer>::New();
  green_renderer->SetViewport(0, 0.5, 0.5, 1);
  green_renderer->AddActor(extract_green_filter_actor);
  green_renderer->ResetCamera();
  auto blue_renderer = vtkSmartPointer<vtkRenderer>::New();
  blue_renderer->SetViewport(0.5, 0.5, 1, 1);
  blue_renderer->AddActor(extract_blue_filter_actor);
  blue_renderer->ResetCamera();

  auto ren_win = vtkSmartPointer<vtkRenderWindow>::New();
  ren_win->AddRenderer(original_renderer);
  ren_win->AddRenderer(red_renderer);
  ren_win->AddRenderer(green_renderer);
  ren_win->AddRenderer(blue_renderer);
  ren_win->SetSize(640, 640);
  ren_win->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  auto int_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(int_style);
  interactor->SetRenderWindow(ren_win);

  interactor->Initialize();
  interactor->Start();

  return 0;
}
