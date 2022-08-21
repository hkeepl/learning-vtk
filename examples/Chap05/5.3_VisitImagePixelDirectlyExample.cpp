/**********************************************************************

  �ļ���: 5.3_VisitImagePixelDirectlyExample.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>

//����ͼ��../data/lena.bmp
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"ImageFile(*.bmp)"<<std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);

	int nbOfComp;
	nbOfComp = reader->GetOutput()->GetNumberOfScalarComponents();

	for(int k=0; k<dims[2]; k++)
	{
		for(int j=0; j<dims[1]; j++)
		{
			for(int i=0; i<dims[0]; i++)
			{
				if(i<100 && j<100)
				{
					unsigned char * pixel = 
						(unsigned char *) ( reader->GetOutput()->GetScalarPointer(i, j, k) );
					*pixel = 0;
					*(pixel+1) = 0;
					*(pixel+2) = 0;
				}
			}
		}
	}

	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("VisitImagePixelDirectlyExample");


	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
