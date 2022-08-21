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

int main(int argc, char *argv[]) {
  if (argc < 2) { // VTK-logo.png
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);

  auto luminance_filter = vtkSmartPointer<vtkImageLuminance>::New();
  luminance_filter->SetInputConnection(reader->GetOutputPort());

  auto orignal_actor = vtkSmartPointer<vtkImageActor>::New();
  orignal_actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

  auto filtered_actor = vtkSmartPointer<vtkImageActor>::New();
  filtered_actor->GetMapper()->SetInputConnection(luminance_filter->GetOutputPort());

  auto original_renderer = vtkSmartPointer<vtkRenderer>::New();
  original_renderer->SetViewport(0, 0, 0.5, 1);
  original_renderer->AddActor(orignal_actor);
  original_renderer->ResetCamera();

  auto filtered_renderer = vtkSmartPointer<vtkRenderer>::New();
  filtered_renderer->SetViewport(0.5, 0, 1, 1);
  filtered_renderer->AddActor(filtered_actor);
  filtered_renderer->ResetCamera();

  auto ren_win = vtkSmartPointer<vtkRenderWindow>::New();
  ren_win->AddRenderer(original_renderer);
  ren_win->AddRenderer(filtered_renderer);
  ren_win->SetSize(640, 320);
  ren_win->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  // 默认 vtkImageViewer2 调整窗宽窗位后，彩色图像会变成灰色图像
  //auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  //viewer->SetInputConnection(reader->GetOutputPort());
  //viewer->SetupInteractor(interactor);

  auto int_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(int_style);
  interactor->SetRenderWindow(ren_win);

  interactor->Initialize();
  interactor->Start();

  return 0;
}
