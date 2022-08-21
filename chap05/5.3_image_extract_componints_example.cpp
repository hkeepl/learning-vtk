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

int main(int argc, char *argv[]) {
  if (argc < 2) { // VTK-logo.png
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  auto extract_red_filter = vtkSmartPointer<vtkImageExtractComponents>::New();
  extract_red_filter->SetComponents(0);
  extract_red_filter->SetInputConnection(reader->GetOutputPort());
  extract_red_filter->Update();
  std::cout << "Scalar Components. Original: " << reader->GetOutput()->GetNumberOfScalarComponents()
            << ", extracted: " << extract_red_filter->GetOutput()->GetNumberOfScalarComponents() << std::endl;
  auto extract_green_filter = vtkSmartPointer<vtkImageExtractComponents>::New();
  extract_green_filter->SetComponents(1);
  extract_green_filter->SetInputConnection(reader->GetOutputPort());
  auto extract_blue_filter = vtkSmartPointer<vtkImageExtractComponents>::New();
  extract_blue_filter->SetComponents(2);
  extract_blue_filter->SetInputConnection(reader->GetOutputPort());


  auto orignal_actor = vtkSmartPointer<vtkImageActor>::New();
  orignal_actor->GetMapper()->SetInputConnection(reader->GetOutputPort());
  auto extract_red_filter_actor = vtkSmartPointer<vtkImageActor>::New();
  extract_red_filter_actor->GetMapper()->SetInputConnection(extract_red_filter->GetOutputPort());
  auto extract_green_filter_actor = vtkSmartPointer<vtkImageActor>::New();
  extract_green_filter_actor->GetMapper()->SetInputConnection(extract_green_filter->GetOutputPort());
  auto extract_blue_filter_actor = vtkSmartPointer<vtkImageActor>::New();
  extract_blue_filter_actor->GetMapper()->SetInputConnection(extract_blue_filter->GetOutputPort());

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
