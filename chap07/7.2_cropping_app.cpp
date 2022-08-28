#include "config.h"

#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkStructuredPoints.h>
#include <vtkGPUVolumeRayCastMapper.h>
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

  auto mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());
  // 设置光线采样间隔
  mapper->SetSampleDistance(mapper->GetSampleDistance() / 4);
  // 设置图像采样步长
  //   mapper->SetAutoAdjustSampleDistances(0);
  //   mapper->SetImageSampleDistance(2);
  mapper->SetAutoAdjustSampleDistances(1);

  // 开启裁剪
  mapper->SetCropping(1);
  // 定义裁剪平面
  mapper->SetCroppingRegionPlanes(100, 200, 100, 200, 100, 200);
  // 定义裁剪显示区域
  mapper->SetCroppingRegionFlags(0x0002000);
  // mapper->SetCroppingRegionFlagsToCross();
  // mapper->SetCroppingRegionFlagsToSubVolume();

  auto property = vtkSmartPointer<vtkVolumeProperty>::New();
  property->SetInterpolationTypeToLinear();
  // 打开或关闭阴影测试
  property->ShadeOn();
  property->SetAmbient(0.4);
  property->SetDiffuse(0.6);
  property->SetSpecular(0.2);
  // 设置灰度不透明度函数
  auto opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
  opacity->AddPoint(70, 0.00);
  opacity->AddPoint(90, 0.40);
  opacity->AddPoint(180, 0.60);
  property->SetScalarOpacity(opacity);
  // 设置颜色传输函数
  auto color = vtkSmartPointer<vtkColorTransferFunction>::New();
  color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
  color->AddRGBPoint(64.00, 1.00, 0.52, 0.80);
  color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
  color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
  property->SetColor(color);

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