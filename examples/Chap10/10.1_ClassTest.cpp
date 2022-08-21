/**********************************************************************

  �ļ���: 10.1_ClassTest.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include "vtkTestClass.h"

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkTestClass> test = vtkSmartPointer<vtkTestClass>::New();
	test->Print(std::cout);

	test->FlagOn();
	test->SetPosition(10, 10, 10);
	test->SetSpeed(1000);
	test->Print(std::cout);

	system("pause");

	return EXIT_SUCCESS;
}