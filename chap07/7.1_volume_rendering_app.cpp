#include "config.h"

#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkStructuredPoints.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAxesActor.h>

int main(int argc, char *argv[]) {
  auto fn = std::string(kRooPath) + "/examples/Chap07/data/mummy.128.vtk";
  if (argc > 1) {
    fn = argv[1];
  }

  auto reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(fn.c_str());
  reader->Update();

  auto mapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());
  // 设置光线采样间隔
  //   mapper->SetSampleDistance(mapper->GetSampleDistance() * 4);
  // 设置图像采样步长
  //   mapper->SetAutoAdjustSampleDistances(0);
  //   mapper->SetImageSampleDistance(4);

  auto property = vtkSmartPointer<vtkVolumeProperty>::New();
  property->SetInterpolationTypeToLinear();
  //! 光照和阴影
  // 环境光系数
  property->SetAmbient(0.4);
  // 散射光系数
  property->SetDiffuse(0.2);
  // 反射光系数
  property->SetSpecular(0.6);
  // 高光强度
  // property->SetSpecularPower(1);
  // 阴影
  // property->ShadeOn();
  //! 灰度不透明度
  // 分段线性标量映射函数，将光线投射过程中的采样点灰度值映射为不同的透明度值
  // 对于不显示的对象，只需要将其对应的灰度范围的不透明度设为0即可
  // auto opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  // opacity->AddPoint(60, 0.00);
  // opacity->AddPoint(120, 0.00);
  // opacity->AddPoint(180, 0.60);
  // property->SetScalarOpacity(opacity);
  //! 梯度不透明度
  auto opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  opacity->AddPoint(40, 0.00);
  opacity->AddPoint(90, 0.50);
  opacity->AddPoint(100, 1.00);
  property->SetGradientOpacity(opacity);
  //! 颜色传输函数
  auto color = vtkSmartPointer<vtkColorTransferFunction>::New();
  color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
  color->AddRGBPoint(64.00, 1.00, 0.52, 0.80);
  color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
  color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
  property->SetColor(color);
  // 1 灰度传输函数
  // 3 RGB
  std::cout << property->GetColorChannels() << std::endl;

  auto volume = vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(mapper);
  volume->SetProperty(property);

  auto ren = vtkSmartPointer<vtkRenderer>::New();
  ren->SetBackground(0.0, 1.0, 0.0);
  ren->AddVolume(volume);

  auto ren_win = vtkSmartPointer<vtkRenderWindow>::New();
  ren_win->AddRenderer(ren);
  ren_win->SetSize(640, 480);
  ren_win->Render();
  ren_win->SetWindowName("VolumeRenderingApp");

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(ren_win);
  ren->ResetCamera();

  ren_win->Render();
  iren->Start();

  return 0;
}