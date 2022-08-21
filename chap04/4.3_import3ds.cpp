#include <vtk3DSImporter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) { 
    exit(-1);
  }

  auto importer = vtkSmartPointer<vtk3DSImporter>::New();
  importer->SetFileName(argv[1]);
  /*打开法向量的计算功能，从图像上看，打开该功能后，图像表面平滑*/
  importer->ComputeNormalsOn();
  importer->Read();

  auto renderer = importer->GetRenderer();
  auto ren_win = importer->GetRenderWindow();
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  ren_win->SetInteractor(interactor);
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
