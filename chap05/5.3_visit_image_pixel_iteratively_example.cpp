#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkImageIterator.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    exit(-1);
  }

  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  int sub_region[6] = {0, 300, 0, 300, 0, 0};
  vtkImageIterator<unsigned char> iter(reader->GetOutput(), sub_region);
  while (!iter.IsAtEnd()) {
    auto si = iter.BeginSpan();
    auto se = iter.EndSpan();
    while (si != se) {
      *si = 255 - *si;
      ++si;
    }
    iter.NextSpan();
  }

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());

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
