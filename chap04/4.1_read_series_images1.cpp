/*
 * 读取PNG，保存为JPG
 */
#include <vtkImageViewer2.h>
#include <vtkStringArray.h>
#include <vtkJPEGReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 2) { // Root path
    exit(-1);
  }
  
  std::string format(argv[1]);
  format += "\\head%03d.jpg";
  auto file_array = vtkSmartPointer<vtkStringArray>::New();
  char filename[128] = {0};
  for(int i = 1; i <= 100; ++i) {
      sprintf(filename, format.c_str(), i);
      file_array->InsertNextValue(filename);
  }
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileNames(file_array);

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->GetRenderWindow()->SetInteractor(interactor);
  viewer->GetRenderer()->ResetCamera();
  viewer->SetSlice(42);
  viewer->SetSliceOrientationToXY();
  viewer->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}
