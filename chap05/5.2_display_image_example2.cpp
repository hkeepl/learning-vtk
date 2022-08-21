#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  auto actor = vtkSmartPointer<vtkImageActor>::New();
  // Set/Get the image data input for the image actor.
  // This is for backwards compatibility, for a proper pipeline connection you should use
  // GetMapper()->SetInputConnection() instead.
  actor->SetInputData(reader->GetOutput());
  // actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.4, 0.5, 0.6);

  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->SetSize(480, 480);
  render_window->AddRenderer(renderer);
  render_window->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->SetRenderWindow(render_window);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
