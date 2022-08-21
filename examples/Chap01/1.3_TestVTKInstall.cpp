/**********************************************************************

  �ļ���: 1.3_TestVTKInstall.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

int main()
{
	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->Render();

	renWin->SetWindowName("TestVTKInstall");
	renWin->SetSize(640, 480);
	renWin->Render();

	std::cin.get();
	return EXIT_SUCCESS;
}
