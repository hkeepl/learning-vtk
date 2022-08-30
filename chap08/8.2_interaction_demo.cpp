#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>

#include "config.h"

int main(int argc, char* argv[])
{
    std::string fn = std::string(kRooPath) + "/examples/Chap08/data/VTKBook-TestImage.jpg";
    if(argc > 1) {
        fn = argv[1];
    }

    auto reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(fn.c_str());
    reader->Update();

	vtkSmartPointer<vtkImageActor> imageActor = 
		vtkSmartPointer<vtkImageActor>::New();
	imageActor->SetInputData( reader->GetOutput() );

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor( imageActor );
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer( renderer );
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("InteractionDemo");

	vtkSmartPointer<vtkRenderWindowInteractor> iren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleImage> style = 
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}
