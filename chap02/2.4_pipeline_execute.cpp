/**
 * 读入.vtk文件，然后通过移动立方体法（vtkMarchingCubes）提取等值面，最后把等值面的数据经Mapper送往渲染引擎进行显示
 */

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <iostream>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  std::cout << "Modification Time of reader (After New()): " << reader->GetMTime() << std::endl;
  reader->SetFileName(argv[1]);
  std::cout << "Modification Time of reader (After SetFileName()): " << reader->GetMTime()
            << std::endl;

  int extent[6];
  vtkImageData* image_data = nullptr;
  {
    image_data = reader->GetOutput();
    std::cout << "Modification Time of reader (After GetOutput()): " << reader->GetMTime()
              << std::endl;

    image_data->GetExtent(extent);
    std::cout << "Extent of image: " << extent[0] << " " << extent[1] << " " << extent[2] << " "
              << extent[3] << " " << extent[4] << " " << extent[5] << std::endl;
  }
  {
    reader->Update();
    std::cout << "Modification Time of reader (After Update()): " << reader->GetMTime()
              << std::endl;

        image_data = reader->GetOutput();
    std::cout << "Modification Time of reader (After GetOutput()): " << reader->GetMTime()
              << std::endl;

    image_data->GetExtent(extent);
    std::cout << "Extent of image: " << extent[0] << " " << extent[1] << " " << extent[2] << " "
              << extent[3] << " " << extent[4] << " " << extent[5] << std::endl;
  }

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputConnection(reader->GetOutputPort());
  viewer->Render();
  viewer->SetSize(640, 480);

  auto render_win_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  auto istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  render_win_interactor->SetInteractorStyle(istyle);
  viewer->SetupInteractor(render_win_interactor);

  render_win_interactor->Initialize();
  render_win_interactor->Start();

  return 0;
}
