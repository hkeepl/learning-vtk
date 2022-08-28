#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODProp3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkProperty.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkCallbackCommand.h>

#include "config.h"

/**
 * vtkLODProp3D用来提高绘制速度
 */
int main(int argc, char *argv[]) {
  auto fn = std::string(kRooPath) + "/examples/Chap07/data/mummy.128.vtk";
  if (argc > 1) {
    fn = argv[1];
  }

  auto reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(fn.c_str());
  reader->Update();

  vtkSmartPointer<vtkVolumeProperty> volumeProperty =
      vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->SetInterpolationTypeToLinear();
  volumeProperty->ShadeOn();
  volumeProperty->SetAmbient(0.4);
  volumeProperty->SetDiffuse(0.6);
  volumeProperty->SetSpecular(0.2);

  vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
      vtkSmartPointer<vtkPiecewiseFunction>::New();
  compositeOpacity->AddPoint(70, 0.00);
  compositeOpacity->AddPoint(90, 0.40);
  compositeOpacity->AddPoint(180, 0.60);
  volumeProperty->SetScalarOpacity(compositeOpacity);

  vtkSmartPointer<vtkColorTransferFunction> color =
      vtkSmartPointer<vtkColorTransferFunction>::New();
  color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
  color->AddRGBPoint(64.00, 1.00, 0.52, 0.30);
  color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
  color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
  volumeProperty->SetColor(color);

  auto hiresMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  hiresMapper->SetInputData(reader->GetOutput());
  hiresMapper->SetAutoAdjustSampleDistances(0);

  auto lowresMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
  lowresMapper->SetInputData(reader->GetOutput());
  lowresMapper->SetAutoAdjustSampleDistances(0);
  lowresMapper->SetSampleDistance(4 * hiresMapper->GetSampleDistance());
  lowresMapper->SetImageSampleDistance(4 * hiresMapper->GetImageSampleDistance());

  vtkSmartPointer<vtkLODProp3D> prop = vtkSmartPointer<vtkLODProp3D>::New();
  prop->AddLOD(lowresMapper, volumeProperty, 0.0);
  prop->AddLOD(hiresMapper, volumeProperty, 4.0);

  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  ren->SetBackground(1.0, 1.0, 1.0);
  ren->AddVolume(prop);

  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);
  renWin->SetSize(640, 480);
  renWin->Render();
  renWin->SetWindowName("7.3_vtkLODProp3DApp");

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  ren->ResetCamera();

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}