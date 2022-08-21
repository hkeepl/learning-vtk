#include <vtkImageActor.h>
#include <vtkImageBlend.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMapper3D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);

  auto source = vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetNumberOfScalarComponents(1);
  source->SetScalarTypeToUnsignedChar();
  source->SetExtent(0, 512, 0, 512, 0, 0);
  source->SetDrawColor(0.0);
  source->FillBox(0, 512, 0, 512);
  source->SetDrawColor(255.0);
  source->FillBox(100, 400, 100, 412);

  auto blend = vtkSmartPointer<vtkImageBlend>::New();
  // Use add Not set
  // Can use AddInputData
  blend->AddInputConnection(reader->GetOutputPort());
  blend->AddInputConnection(source->GetOutputPort());
  blend->SetOpacity(0, 0.6);
  blend->SetOpacity(1, 0.4);

  auto original_actor = vtkSmartPointer<vtkImageActor>::New();
  original_actor->GetMapper()->SetInputConnection(reader->GetOutputPort());
  auto renderer1 = vtkSmartPointer<vtkRenderer>::New();
  renderer1->SetViewport(0, 0, 0.33, 1);
  renderer1->AddActor(original_actor);
  renderer1->ResetCamera();
  renderer1->SetBackground(0.4, 0.5, 0.6);

  auto source_actor = vtkSmartPointer<vtkImageActor>::New();
  source_actor->GetMapper()->SetInputConnection(source->GetOutputPort());
  auto renderer2 = vtkSmartPointer<vtkRenderer>::New();
  renderer2->SetViewport(0.33, 0, 0.66, 1);
  renderer2->AddActor(source_actor);
  renderer2->ResetCamera();
  renderer2->SetBackground(0.4, 0.5, 0.6);

  auto blend_actor = vtkSmartPointer<vtkImageActor>::New();
  blend_actor->GetMapper()->SetInputConnection(blend->GetOutputPort());
  auto renderer3 = vtkSmartPointer<vtkRenderer>::New();
  renderer3->SetViewport(0.66, 0, 1, 1);
  renderer3->AddActor(blend_actor);
  renderer3->ResetCamera();
  renderer3->SetBackground(0.4, 0.5, 0.6);

  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->SetSize(640, 320);
  render_window->AddRenderer(renderer1);
  render_window->AddRenderer(renderer2);
  render_window->AddRenderer(renderer3);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->SetRenderWindow(render_window);
  render_window->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}
