#include <iostream>
#include <vtkBMPReader.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  int dims[3] = {0};
  double origin[3] = {0};
  double spacing[3] = {0};

  reader->GetOutput()->GetDimensions(dims);
  std::cout << "Image dimensions: " << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
  reader->GetOutput()->GetOrigin(origin);
  std::cout << "Image origin: " << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;
  reader->GetOutput()->GetSpacing(spacing);
  std::cout << "Image spacing: " << spacing[0] << " " << spacing[1] << " " << spacing[2]
            << std::endl;

  auto changer = vtkSmartPointer<vtkImageChangeInformation>::New();
  changer->SetInputConnection(reader->GetOutputPort());
  changer->SetOutputOrigin(100, 100, 0);
  changer->SetOutputSpacing(5, 5, 1);
  changer->SetCenterImage(1);
  changer->Update();

  changer->GetOutput()->GetDimensions(dims);
  std::cout << "Image changed dimensions: " << dims[0] << " " << dims[1] << " " << dims[2] << std::endl;
  changer->GetOutput()->GetOrigin(origin);
  std::cout << "Image changed origin: " << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;
  changer->GetOutput()->GetSpacing(spacing);
  std::cout << "Image changed spacing: " << spacing[0] << " " << spacing[1] << " " << spacing[2]
            << std::endl;

  /* 图像显示 */
  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(changer->GetOutputPort());

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);
  viewer->Render();
  viewer->GetRenderer()->ResetCamera();
  viewer->Render();
  viewer->SetSize(640, 320);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
