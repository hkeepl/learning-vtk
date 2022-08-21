/**********************************************************************

  �ļ���: 8.1_ObserverCommandDemo2.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkCommand.h>
#include <vtkBoxWidget.h>
#include <vtkTransform.h>
#include <vtkInteractorStyleTrackballCamera.h>

//��һ��
class vtkMyCallback : public vtkCommand
{
public:
	static vtkMyCallback *New() 
	{ return new vtkMyCallback; }

	void SetObject(vtkConeSource* cone)
	{
		m_Cone = cone;
	}

	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData)
	{
		std::cout<<"Left button pressed.\n"
			<<"The Height: "<<m_Cone->GetHeight()<<"\n"
			<<"The Radius: "<<m_Cone->GetRadius()<<std::endl;
	}

private:
	vtkConeSource *m_Cone;
};

int main()
{
	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
	cone->SetHeight( 3.0 );
	cone->SetRadius( 1.0 );
	cone->SetResolution( 10 );

	vtkSmartPointer<vtkPolyDataMapper> coneMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputConnection( cone->GetOutputPort() );

	vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper( coneMapper );

	vtkSmartPointer<vtkRenderer> ren1= vtkSmartPointer<vtkRenderer>::New();
	ren1->AddActor( coneActor );
	ren1->SetBackground( 1.0, 1.0, 1.0 );

	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer( ren1 );
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("ObserverCommandDemo2");

	vtkSmartPointer<vtkRenderWindowInteractor> iren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);

	//�ڶ���
	vtkSmartPointer<vtkMyCallback> callback = vtkSmartPointer<vtkMyCallback>::New();
	callback->SetObject(cone);

	//������
	iren->AddObserver(vtkCommand::LeftButtonPressEvent, callback);

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}