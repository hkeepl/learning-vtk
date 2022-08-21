#include <iostream>

#include <vtkSmartPointer.h>
// 继承vtkPolyDataAlgorithm，生成数据类型是VTKPolyData，生成一个中心在渲染场景原点的圆柱
#include <vtkCylinderSource.h>
// 继承vtkMapper, 用于渲染vtkPolyData类型的数据，作用是将输入的数据转换为几何图元（点，线，多边形）进行渲染
#include <vtkPolyDataMapper.h>
//
// 继承vtkProp，渲染场景中的可视化表达通过vtkProp子类负责。依赖两个对象：vtkMapper（存放数据和渲染信息）和vtkProperty（负责控制颜色，不透明度等参数）。
// 另外，vtkActor中还可以设置纹理对象vtkTexture，用于纹理贴图
// 
// VTK定义了大量vtkProp的子类，如vtkImageActor，vtkPieChartActor。
// 其中有一些Prop内部包含了控制显示的参数和待渲染数据的索引，因此不需要额外的Property和Mapper。
//
#include <vtkActor.h>
//
// 继承VTKViewPort
// 负责管理场景的渲染过程，组成场景的对象包括Prop，Camera和Light。
//
#include <vtkRenderer.h>
// vtkRenderWindow 将操作系统和VTK渲染引擎连接到一起。
// 
// RenderWindow 就是一个用户界面的窗口，里面可以放置多个renderer（用来显示图像）
// 
// vtkRenderWindow中包含了vtkRenderer集合，渲染参数等。
//
#include <vtkRenderWindow.h>
//
// 提供平台独立的响应鼠标，键盘和始终事件的交互机制。
// 必须要给交互器对象设置渲染窗口！因为消息是通过渲染窗口捕获到的。
//
#include <vtkRenderWindowInteractor.h>
//
// 交互器样式的一种
//
#include <vtkInteractorStyleTrackballCamera.h>


int main() {
  auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(3.0); //Question 这里设置高度和半径，数值的单位是什么？
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->SetSize(420, 128); // 单位：像素

  auto render_win_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  render_win_interactor->SetRenderWindow(render_win);

  auto istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  render_win_interactor->SetInteractorStyle(istyle);

  render_win_interactor->Initialize(); // 初始化，为处理窗口事件做准备
  render_win_interactor->Start(); // 等待用户交互事件的发生

  return 0;
}