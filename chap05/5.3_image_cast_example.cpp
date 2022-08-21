#include <vtkMetaImageReader.h>
#include <vtkBMPReader.h>
#include <vtkImageCast.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(-1);
  }

  auto reader = vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  auto img_cast = vtkSmartPointer<vtkImageCast>::New();
  img_cast->SetInputData(reader->GetOutput());
  img_cast->SetOutputScalarTypeToFloat();

  auto img_shift_scale = vtkSmartPointer<vtkImageShiftScale>::New();
  img_shift_scale->SetInputData(reader->GetOutput());
  img_shift_scale->SetOutputScalarTypeToFloat();
  img_shift_scale->SetShift(1);
  img_shift_scale->SetScale(100);

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(img_cast->GetOutputPort());

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);
  viewer->Render();
  viewer->GetRenderer()->ResetCamera();
  viewer->Render();

  viewer->GetRenderer()->SetBackground(1, 1, 1);
  viewer->SetSize(640, 480);

  interactor->Initialize();
  interactor->Start();

  return 0;
}
