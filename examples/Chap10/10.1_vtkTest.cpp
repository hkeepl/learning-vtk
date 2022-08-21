/**********************************************************************

  �ļ���: 10.1_vtkTest.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageCast.h>
#include <vtkDataSetReader.h>
#include <vtkSmartPointer.h>
#include <vtkLight.h>

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkLight> light1
		= vtkSmartPointer<vtkLight>::New();
	std::cout<<"//////////////////////////////"<<std::endl;
	std::cout<<"Reference Count of light1 is:"<<light1->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkLight> light2 = light1;
	std::cout<<"//////////////////////////////"<<std::endl;
	std::cout<<"Reference Count of light1 is:"<<light1->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of light2 is:"<<light2->GetReferenceCount()<<std::endl;

	vtkLight* light3 = vtkLight::New();
	std::cout<<"//////////////////////////////"<<std::endl;
	std::cout<<"Reference Count of light3 is:"<<light3->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkLight> light4 = light3;
	std::cout<<"//////////////////////////////"<<std::endl;
	std::cout<<"Reference Count of light3 is:"<<light3->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of light4 is:"<<light4->GetReferenceCount()<<std::endl;

	vtkLight* light5 = light1;
	std::cout<<"//////////////////////////////"<<std::endl;
	std::cout<<"Reference Count of light1 is:"<<light1->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of light5 is:"<<light2->GetReferenceCount()<<std::endl;

	system("pause");

	return EXIT_SUCCESS;
}