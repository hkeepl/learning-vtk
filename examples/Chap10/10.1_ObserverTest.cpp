/**********************************************************************

  �ļ���: 10.1_ObserverTest.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include "vtkTestFilter.h"
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>

void CallbackFunction(vtkObject* caller,
					  long unsigned int eventId,
					  void* clientData, void* callData )
{
	int* callDataCasted = reinterpret_cast<int*>(callData);
	std::cout << *callDataCasted << std::endl;
}

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkTestFilter> filter =
		vtkSmartPointer<vtkTestFilter>::New();

	vtkSmartPointer<vtkCallbackCommand> callback =
		vtkSmartPointer<vtkCallbackCommand>::New();
	callback->SetCallback(CallbackFunction );

	filter->AddObserver(MyEvent, callback);
	filter->Update();

	system("pause");

	return EXIT_SUCCESS;
}