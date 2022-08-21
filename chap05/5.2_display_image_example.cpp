#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>

int main(int argc, char *argv[])
{
  if(argc < 2) {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());
  viewer->SetColorLevel(500);
  viewer->SetColorWindow(2000);
  viewer->SetSlice(16);
  viewer->SetSliceOrientationToXY();
  viewer->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);
  interactor->Initialize();
  interactor->Start();
  
  return 0;
}
