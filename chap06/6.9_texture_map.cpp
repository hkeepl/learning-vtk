#include "config.h"

#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkTexture.h>
#include <vtkTextureMapToCylinder.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[]) {
  auto texture_fn = std::string(kRooPath) + "/examples/Chap06/data/masonry.bmp";
  auto polydata_fn = std::string(kRooPath) + "/examples/Chap06/data/cow.vtp";
  if (argc > 1) {
    texture_fn = argv[1];
  }
  if (argc > 2) {
    polydata_fn = argv[2];
  }

  // 读取图片
  auto texture_reader = vtkSmartPointer<vtkBMPReader>::New();
  texture_reader->SetFileName(texture_fn.c_str());
  // 图片转成纹理
  auto texture = vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(texture_reader->GetOutputPort());

  // 读入polydata
  auto polydata_reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  polydata_reader->SetFileName(polydata_fn.c_str());
  // 实现纹理空间到模型空间的映射关系
  auto texture_map = vtkSmartPointer<vtkTextureMapToCylinder>::New();
  texture_map->SetInputConnection(polydata_reader->GetOutputPort());

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(texture_map->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  // 设置纹理
  actor->SetTexture(texture);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->AddRenderer(renderer);
  render_window->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(render_window);
  interactor->Initialize();
  interactor->Start();

  return 0;
}