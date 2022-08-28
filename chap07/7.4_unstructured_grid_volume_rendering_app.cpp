#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridVolumeRayCastMapper.h>
#include <vtkUnstructuredGridVolumeZSweepMapper.h>
#include <vtkProjectedTetrahedraMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredPointsReader.h>
#include <vtkSLCReader.h>
#include <vtkStructuredPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkThreshold.h>
#include <vtkDataSetTriangleFilter.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkStdString.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTesting.h>

#include "config.h"

int main(int argc, char *argv[]) {
  auto fn = std::string(kRooPath) + "/examples/Chap07/data/ironProt.vtk";
  if (argc > 1) {
    fn = argv[1];
  }

  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
  ren->SetBackground(1.0, 1.0, 1.0);

  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  iren->SetDesiredUpdateRate(10);

  vtkSmartPointer<vtkStructuredPointsReader> reader =
      vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(fn.c_str());

  vtkSmartPointer<vtkThreshold> thresh = vtkSmartPointer<vtkThreshold>::New();
//   thresh->ThresholdByUpper(80);
  thresh->SetLowerThreshold(80);
  thresh->AllScalarsOff();
  thresh->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkDataSetTriangleFilter> trifilter =
      vtkSmartPointer<vtkDataSetTriangleFilter>::New();
  trifilter->SetInputConnection(thresh->GetOutputPort());

  vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction =
      vtkSmartPointer<vtkPiecewiseFunction>::New();
  opacityTransferFunction->AddPoint(80.0, 0.0);
  opacityTransferFunction->AddPoint(120.0, 0.2);
  opacityTransferFunction->AddPoint(255.0, 0.2);

  vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction =
      vtkSmartPointer<vtkColorTransferFunction>::New();
  colorTransferFunction->AddRGBPoint(80.0, 0.0, 0.0, 0.0);
  colorTransferFunction->AddRGBPoint(120.0, 0.0, 0.0, 1.0);
  colorTransferFunction->AddRGBPoint(160.0, 1.0, 0.0, 0.0);
  colorTransferFunction->AddRGBPoint(200.0, 0.0, 1.0, 0.0);
  colorTransferFunction->AddRGBPoint(255.0, 0.0, 1.0, 1.0);

  vtkSmartPointer<vtkVolumeProperty> volumeProperty =
      vtkSmartPointer<vtkVolumeProperty>::New();
  volumeProperty->SetColor(colorTransferFunction);
  volumeProperty->SetScalarOpacity(opacityTransferFunction);
  volumeProperty->ShadeOff();
  volumeProperty->SetInterpolationTypeToLinear();

  vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
  volume->SetProperty(volumeProperty);

  int RenderType = 1;
  if (RenderType == 1) {
    // 效果最好
    vtkSmartPointer<vtkUnstructuredGridVolumeRayCastMapper> volumeMapper =
        vtkSmartPointer<vtkUnstructuredGridVolumeRayCastMapper>::New();
    volumeMapper->SetInputConnection(trifilter->GetOutputPort());
    volume->SetMapper(volumeMapper);
    ren->AddVolume(volume);
  } else if (RenderType == 2) {
    vtkSmartPointer<vtkUnstructuredGridVolumeZSweepMapper> volumeMapper =
        vtkSmartPointer<vtkUnstructuredGridVolumeZSweepMapper>::New();
    volumeMapper->SetInputConnection(trifilter->GetOutputPort());
    volume->SetMapper(volumeMapper);
    ren->AddVolume(volume);
  } else if (RenderType == 3) {
    vtkSmartPointer<vtkProjectedTetrahedraMapper> volumeMapper =
        vtkSmartPointer<vtkProjectedTetrahedraMapper>::New();
    volumeMapper->SetInputConnection(trifilter->GetOutputPort());
    volume->SetMapper(volumeMapper);
    ren->AddVolume(volume);
  } 

  renWin->SetSize(640, 480);
  renWin->Render();
  renWin->SetWindowName("UnstructuredGridVolumeRendering");

  renWin->Render();
  iren->Start();

  return EXIT_SUCCESS;
}