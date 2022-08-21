#include <iostream>
#include <vtkBMPReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  int dims[3] = {0};
  reader->GetOutput()->GetDimensions(dims);
  std::cout << "Image dimensions: " << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
  
  double origin[3] = {0};
  reader->GetOutput()->GetOrigin(origin);
  std::cout << "Image origin: " << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;

  double spacing[3] = {0};
  reader->GetOutput()->GetSpacing(spacing);
  std::cout << "Image spacing: " << spacing[0] << " " << spacing[1] << " " << spacing[2] << std::endl;

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);
  viewer->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}
