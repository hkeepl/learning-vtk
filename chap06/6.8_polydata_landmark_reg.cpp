#include "config.h"

#include <vtkSmartPointer.h>
#include <vtkLandmarkTransform.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkAxesActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[]) {
  auto src_points = vtkSmartPointer<vtkPoints>::New();
  src_points->InsertNextPoint(0.5, 0.0, 0.0);
  src_points->InsertNextPoint(0.0, 0.5, 0.0);
  src_points->InsertNextPoint(0.0, 0.0, 0.5);

  auto tgt_points = vtkSmartPointer<vtkPoints>::New();
  tgt_points->InsertNextPoint(0.0, 0.0, 0.55);
  tgt_points->InsertNextPoint(0.0, 0.55, 0.0);
  tgt_points->InsertNextPoint(-0.55, 0.0, 0.0);

  auto landmark = vtkSmartPointer<vtkLandmarkTransform>::New();
  landmark->SetSourceLandmarks(src_points);
  landmark->SetTargetLandmarks(tgt_points);
  landmark->SetModeToRigidBody();
  landmark->Update();

  auto src = vtkSmartPointer<vtkPolyData>::New();
  src->SetPoints(src_points);

  auto tgt = vtkSmartPointer<vtkPolyData>::New();
  tgt->SetPoints(tgt_points);

  auto src_glyph_filter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
  src_glyph_filter->SetInputData(src);

  auto tgt_glyph_filter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
  tgt_glyph_filter->SetInputData(tgt);

  auto transform_filter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transform_filter->SetInputData(src);
  transform_filter->SetTransform(landmark);
  transform_filter->Update();

  // 源编辑点 {红}
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(src_glyph_filter->GetOutputPort());
  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1, 0, 0);
  actor->GetProperty()->SetPointSize(5);
  // 目标标记点 {绿}
  auto mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(tgt_glyph_filter->GetOutputPort());
  auto actor2 = vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
  actor2->GetProperty()->SetColor(0, 1, 0);
  actor2->GetProperty()->SetPointSize(5);
  // 配准后的点集 {蓝}，其中{蓝}和{绿}应该非常接近
  auto mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper3->SetInputConnection(transform_filter->GetOutputPort());
  auto actor3 = vtkSmartPointer<vtkActor>::New();
  actor3->SetMapper(mapper3);
  actor3->GetProperty()->SetColor(0, 0, 1);
  actor3->GetProperty()->SetPointSize(5);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->AddActor(actor2);
  renderer->AddActor(actor3);

  auto axes = vtkSmartPointer<vtkAxesActor>::New();
  //? 不明白SetScale的作用
  //   axes->SetScale(30);
  renderer->AddActor(axes);
  renderer->SetBackground(0.3, 0.6, 0.3);

  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->AddRenderer(renderer);
  render_window->Render();

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(render_window);
  interactor->Initialize();
  interactor->Start();

  return 0;
}