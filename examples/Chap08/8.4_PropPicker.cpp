/**********************************************************************

  �ļ���: 8.4_PropPicker.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

// Handle mouse events
class PropPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static PropPickerInteractorStyle* New();
	vtkTypeMacro(PropPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

	PropPickerInteractorStyle()
	{
		LastPickedActor = NULL;
		LastPickedProperty = vtkProperty::New();
	}
	virtual ~PropPickerInteractorStyle()
	{
		LastPickedProperty->Delete();
	}
	virtual void OnLeftButtonDown()
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkPropPicker>  picker =
			vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		double* pos = picker->GetPickPosition();
		// If we picked something before, reset its property
		if (this->LastPickedActor)
		{
			this->LastPickedActor->GetProperty()->DeepCopy(this->LastPickedProperty);
		}
		this->LastPickedActor = picker->GetActor();
		if (this->LastPickedActor)
		{
			// Save the property of the picked actor so that we can restore it next time
			this->LastPickedProperty->DeepCopy(this->LastPickedActor->GetProperty());
			// Highlight the picked actor by changing its properties
			this->LastPickedActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
			this->LastPickedActor->GetProperty()->SetDiffuse(1.0);
			this->LastPickedActor->GetProperty()->SetSpecular(0.0);
		}

		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}

private:
	vtkActor    *LastPickedActor;
	vtkProperty *LastPickedProperty;
};

vtkStandardNewMacro(PropPickerInteractorStyle);

int main(int argc, char *argv[])
{
	int numberOfSpheres = 10;
	if (argc > 1)
	{
		numberOfSpheres = atoi(argv[1]);
	}
	// A renderer and render window
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->Render();
	renderWindow->SetWindowName("PropPicker");
	renderWindow->AddRenderer ( renderer );

	// An interactor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow ( renderWindow );

	// Set the custom type to use for interaction.
	vtkSmartPointer<PropPickerInteractorStyle> style =
		vtkSmartPointer<PropPickerInteractorStyle>::New();
	style->SetDefaultRenderer(renderer);

	renderWindowInteractor->SetInteractorStyle( style );

	for (int i = 0; i < numberOfSpheres; ++i)
	{
		vtkSmartPointer<vtkSphereSource> source =
			vtkSmartPointer<vtkSphereSource>::New();
		double x, y, z, radius;
		x = vtkMath::Random(-5,5);
		y = vtkMath::Random(-5,5);
		z = vtkMath::Random(-5,5);
		radius = vtkMath::Random(.5, 1.0);
		source->SetRadius(radius);
		source->SetCenter(x, y, z);
		source->SetPhiResolution(11);
		source->SetThetaResolution(21);
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection ( source->GetOutputPort());
		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		actor->SetMapper ( mapper );
		double r, g, b;
		r = vtkMath::Random(.4, 1.0);
		g = vtkMath::Random(.4, 1.0);
		b = vtkMath::Random(.4, 1.0);
		actor->GetProperty()->SetDiffuseColor(r, g, b);
		actor->GetProperty()->SetDiffuse(.8);
		actor->GetProperty()->SetSpecular(.5);
		actor->GetProperty()->SetSpecularColor(1.0,1.0,1.0);
		actor->GetProperty()->SetSpecularPower(30.0);
		renderer->AddActor ( actor );
	}

	renderer->SetBackground ( 1.0, 1.0, 1.0 );

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}