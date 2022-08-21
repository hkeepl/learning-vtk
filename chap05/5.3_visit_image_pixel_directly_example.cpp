#include <vtkBMPReader.h>
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

  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  auto image_data = reader->GetOutput();

  int dims[3] = {0};
  reader->GetOutput()->GetDimensions(dims);

  int num_of_comp = reader->GetOutput()->GetNumberOfScalarComponents();
  std::cout << num_of_comp << std::endl;

  for (int k = 0; k < dims[2]; ++k) {
    for (int j = 0; j < dims[1]; ++j) {
      for (int i = 0; i < dims[0]; ++i) {
        if (i < 100 && j < 100) {
          auto pixel = reinterpret_cast<unsigned char *>(reader->GetOutput()->GetScalarPointer(i, j, k));
          for (int nc = 0; nc < num_of_comp; ++nc) {
              *(pixel + nc) = 0;
          }
          //*(pixel + 0) = 0;
          //*(pixel + 1) = 0;
          //*(pixel + 2) = 0;
        }
      }
    }
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
