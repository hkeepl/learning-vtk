/*
 * 读取PNG，保存为JPG
 */
#include <string>
#include <vtkImageAppend.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[]) {
  if (argc < 2) { // Root path
    exit(-1);
  }

  auto append = vtkSmartPointer<vtkImageAppend>::New();
  append->SetAppendAxis(2); // 设置在Z轴方向上追加

  std::string format(argv[1]);
  format += "\\head%03d.jpg";
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  char filename[128] = {0};
  for (int i = 1; i <= 100; ++i) {
    sprintf(filename, format.c_str(), i);
    reader->SetFileName(filename);
    append->AddInputConnection(reader->GetOutputPort());
  }

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort()); //! 注意，数据还是在Reader管道节点上
  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(interactor_style);
  viewer->GetRenderWindow()->SetInteractor(interactor);
  viewer->GetRenderer()->ResetCamera();
  viewer->SetSliceOrientationToXY();
  viewer->Render();
  interactor->Initialize();
  interactor->Start();

  return 0;
}
