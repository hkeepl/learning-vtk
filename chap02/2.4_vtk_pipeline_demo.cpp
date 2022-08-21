/**
 * 读入.vtk文件，然后通过移动立方体法（vtkMarchingCubes）提取等值面，最后把等值面的数据经Mapper送往渲染引擎进行显示
 */

#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main(int argc, char* argv[]) {
  if (argc < 2)
  {
    exit(-1);
  }
  auto reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(argv[1]);

  auto marching_cubes = vtkSmartPointer<vtkMarchingCubes>::New();
  marching_cubes->SetInputConnection(reader->GetOutputPort());
  marching_cubes->SetValue(0, 256);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(marching_cubes->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->SetSize(640, 480);

  auto render_win_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  render_win_interactor->SetRenderWindow(render_win);

  auto istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  render_win_interactor->SetInteractorStyle(istyle);

  render_win_interactor->Initialize();
  render_win_interactor->Start();

  return 0;
}
