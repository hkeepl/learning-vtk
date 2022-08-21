/*
 * 读取PNG，保存为JPG
 */
#include <string>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) { // Root path
    exit(-1);
  }

  std::string prefix(argv[1]);
  prefix += "\\head";
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFilePrefix(prefix.c_str());
  reader->SetFilePattern("%s%03d.jpg");
  reader->SetDataExtent(0, 255, 0, 255, 1, 100);
  reader->Update();

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->GetRenderWindow()->SetInteractor(interactor);
  viewer->GetRenderer()->ResetCamera();
  viewer->SetSliceOrientationToXY();
  viewer->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}
