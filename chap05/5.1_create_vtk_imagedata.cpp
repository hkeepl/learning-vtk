#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <iostream>

int main() {
  vtkSmartPointer<vtkImageData> img = vtkSmartPointer<vtkImageData>::New();
  img->SetDimensions(16, 16, 1);
  img->AllocateScalars(VTK_UNSIGNED_CHAR, 1); // Transition from VTK5 to VTK6
  auto *ptr = reinterpret_cast<unsigned char *>(img->GetScalarPointer());
  for (int i = 0; i < 16; i++) {
    int val = i * 16 % 256;
    std::cout << val << std::endl;
    for (int j = 0; j < 16; j++) {
      *ptr = val;
      ++ptr;
    }
  }
  // 从显示的图像看，图像左下角是开始的位置，按行赋值

  auto actor = vtkSmartPointer<vtkImageActor>::New();
  actor->SetInputData(img);
  actor->InterpolateOff();

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->SetViewport(0, 0, 1, 1);
  renderer->AddActor(actor);
  renderer->ResetCamera();
  renderer->SetBackground(1, 1, 1);

  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->SetSize(640, 480);
  render_window->AddRenderer(renderer);
  render_window->Render();
  render_window->SetWindowName("CreateVTKImageData");

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->SetRenderWindow(render_window);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
