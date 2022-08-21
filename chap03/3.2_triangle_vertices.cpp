#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[]) {
  /* 赋值方法1 */
  // auto points = vtkSmartPointer<vtkPoints>::New();
  // auto point_id1 = points->InsertNextPoint(1.0, 0.0, 0.0); // id: 0
  // auto point_id2 = points->InsertNextPoint(0.0, 0.0, 1.0); // id: 1
  // auto point_id3 = points->InsertNextPoint(0.0, 0.0, 0.0); // id: 2

  // auto vertices = vtkSmartPointer<vtkCellArray>::New();
  // vertices->InsertNextCell(1, &point_id1);
  // vertices->InsertNextCell(1, &point_id2);
  // vertices->InsertNextCell(1, &point_id3);

  /* 赋值方法2 */
  //创建点的坐标
  double X[3] = {1.0, 0.0, 0.0};
  double Y[3] = {0.0, 0.0, 1.0};
  double Z[3] = {0.0, 0.0, 0.0};

  //创建点数据以及在每个点坐标上加入(顶点)Vertex这种Cell
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

  for (unsigned int i = 0; i < 3; ++i) {
    //定义用于存储点索引的中间变量，vtkIdType就相当于int或long型
    vtkIdType pid[1];

    //把每个点坐标加入到vtkPoints中，InsertNextPoint()返回加入的点的索引号，
    //下面我们需要使用这个索引号来创建Vertex类型的Cell
    pid[0] = points->InsertNextPoint(X[i], Y[i], Z[i]);

    //在每个坐标点上分别创建一个Vertex，Vertex是Cell里的一种
    vertices->InsertNextCell(1, pid);
  }

  /* 根据坐标位置和拓扑结构生成多边形数据 */

  auto polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetLines(vertices);

  auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName("triangle_vertices.vtk");
  writer->SetInputData(polydata);
  writer->Write();

  /* Show polydata */

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polydata);

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(render_win);
  auto interactor_style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle(interactor_style);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
