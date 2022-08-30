#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>

#include "config.h"

class MyCommand : public vtkCommand {
public:
  static MyCommand *New();
  vtkBaseTypeMacro(MyCommand, vtkCommand);

  void SetObject(vtkConeSource *cone) { cone_ = cone; }

  void Execute(vtkObject *caller, unsigned long eventId, void *callData) override {
    std::cout << "Left button pressed.\n"
              << "The Height: " << cone_->GetHeight() << "\n"
              << "The Radius: " << cone_->GetRadius() << std::endl;
  }

private:
  vtkConeSource *cone_;
};

vtkStandardNewMacro(MyCommand);

int main(int argc, char *argv[]) {
  std::string fn = std::string(kRooPath) + "/examples/Chap08/data/VTK-logo.png";
  if (argc > 1) {
    fn = argv[1];
  }

  auto cone = vtkSmartPointer<vtkConeSource>::New();
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cone->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.5, 0.7, 0.5);

  auto render_win = vtkSmartPointer<vtkRenderWindow>::New();
  render_win->AddRenderer(renderer);
  render_win->SetSize(640, 480);
  render_win->SetWindowName("ObserverCommandDemo1");

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(render_win);

  auto my_command = vtkSmartPointer<MyCommand>::New();
  my_command->SetObject(cone);
  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, my_command);

  interactor->Initialize();
  interactor->Start();

  return EXIT_SUCCESS;
}