/*
 * 读取PNG，保存为JPG
 */
#include <vtkImageViewer2.h>
#include <vtkJPEGWriter.h>
#include <vtkPNGReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {// VTK-logo.png
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);
  // reader->Update();

  auto writer = vtkSmartPointer<vtkJPEGWriter>::New();
  writer->SetFileName("vtk-logo.jpg");
  writer->SetInputConnection(reader->GetOutputPort());
  writer->Write();

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
