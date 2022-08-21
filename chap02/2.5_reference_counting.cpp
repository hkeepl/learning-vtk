/**
 * 读入.vtk文件，然后通过移动立方体法（vtkMarchingCubes）提取等值面，最后把等值面的数据经Mapper送往渲染引擎进行显示
 */

#include <vtkActor.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <iostream>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    exit(-1);
  }
  {
    auto temp = vtkBMPReader::New();
    std::cout << "Reference count of temp = " << temp->GetReferenceCount() << std::endl; //? 为什么等于2
  }
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->Print(std::cout);
  std::cout << "Reference count of reader = " << reader->GetReferenceCount() << std::endl; //? 为什么等于2
  reader->SetFileName(argv[1]);
  reader->Update();
  reader->Print(std::cout);

  std::cout << "Reference count of reader->GetOutput(Before assignment) = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;

  auto image = reader->GetOutput();
  std::cout << "Reference count of reader->GetOutput(Assign to image) = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;
  std::cout << "Reference count of image = " << image->GetReferenceCount() << std::endl;

  vtkSmartPointer<vtkImageData> image1 = reader->GetOutput();
  std::cout << "Reference count of reader->GetOutput(Assign to image1) = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;
  std::cout << "Reference count of image1 = " << image1->GetReferenceCount() << std::endl;

  vtkSmartPointer<vtkImageData> image2 = reader->GetOutput();
  std::cout << "Reference count of reader->GetOutput(Assign to image2) = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;
  std::cout << "Reference count of image2 = " << image2->GetReferenceCount() << std::endl;

  std::cout << "Reference count of reader = " << reader->GetReferenceCount() << std::endl;

  return 0;
}
