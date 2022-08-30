#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCallbackCommand.h>
#include <vtkRenderer.h>

#include "config.h"

long gPressCounts = 0;

void callbackFunc(vtkObject* caller, unsigned long eid, void* clientdata, void* calldata) {
    std::cout << "You have clicked: " << ++gPressCounts << std::endl;
}

int main(int argc, char *argv[]) {
    std::string fn = std::string(kRooPath) + "/examples/Chap08/data/VTK-logo.png";
    if(argc > 1) {
        fn = argv[1];
    }

    auto reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(fn.c_str());

    auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputConnection(reader->GetOutputPort());

    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    viewer->SetupInteractor(interactor);
    viewer->Render();

    viewer->GetRenderer()->SetBackground(1.0, 0.7, 0.5);
    viewer->SetSize(640, 480);
    viewer->GetRenderWindow()->SetWindowName("ObserverCommandDemo1");

    auto callback = vtkSmartPointer<vtkCallbackCommand>::New();
    callback->SetCallback(callbackFunc);
    interactor->AddObserver(vtkCommand::LeftButtonPressEvent, callback);

    interactor->Initialize();
    interactor->Start();

    return EXIT_SUCCESS;
}