/*
 * 读取PNG，保存为JPG
 */
#include <vtkImageViewer2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) { // VTK-logo
    exit(-1);
  }
  auto reader_factory = vtkSmartPointer<vtkImageReader2Factory>::New();
  auto reader = reader_factory->CreateImageReader2(argv[1]);
  if(nullptr == reader) {
      exit(-1);
  }
  reader->SetFileName(argv[1]);
  reader->Update();

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->GetRenderWindow()->SetInteractor(interactor);
  viewer->GetRenderer()->ResetCamera();
  viewer->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}
