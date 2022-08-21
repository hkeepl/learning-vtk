/**********************************************************************

  �ļ���: 2.2_TextureExample.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkTexture.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

//�����ļ���data/texture.jpg
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer< vtkJPEGReader > reader = 
		vtkSmartPointer< vtkJPEGReader >::New();
	reader->SetFileName(argv[1]);
	
	vtkSmartPointer< vtkTexture > texture = 
		vtkSmartPointer< vtkTexture >::New();
	texture->SetInputConnection( reader->GetOutputPort() );
	texture->InterpolateOn();

	vtkSmartPointer< vtkPlaneSource > plane = 
		vtkSmartPointer< vtkPlaneSource >::New();
	vtkSmartPointer< vtkPolyDataMapper > mapper = 
		vtkSmartPointer< vtkPolyDataMapper >::New();
	mapper->SetInputConnection( plane->GetOutputPort() );

	vtkSmartPointer< vtkActor > actor = 
		vtkSmartPointer< vtkActor >::New();
	actor->SetMapper( mapper );
	actor->SetTexture( texture );

    vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor( actor );
    renderer->SetBackground( 1.0, 1.0, 1.0);
  
    vtkSmartPointer<vtkRenderWindow> renWin = 
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer( renderer );
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("TextureExample");
   
    vtkSmartPointer<vtkRenderWindowInteractor> iren = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
	iren->Initialize();
    iren->Start();
	
	return EXIT_SUCCESS;
}