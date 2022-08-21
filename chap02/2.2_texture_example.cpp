#include <iostream>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkJPEGReader.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTexture.h>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "Texture filename should be entered.";
    exit(1);
  }
  std::cout << argv[1] << std::endl;

  auto reader = vtkSmartPointer<vtkJPEGReader>::New();
  reader->SetFileName(argv[1]);
  auto texture = vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(reader->GetOutputPort());

  auto plane = vtkSmartPointer<vtkPlaneSource>::New();
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(plane->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetTexture(texture);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->SetSize(420, 128);

  auto render_win_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  render_win_interactor->SetRenderWindow(render_win);

  auto istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  render_win_interactor->SetInteractorStyle(istyle);

  render_win_interactor->Initialize();
  render_win_interactor->Start();

  return 0;
}