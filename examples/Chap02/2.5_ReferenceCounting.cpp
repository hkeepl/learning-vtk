/**********************************************************************

  �ļ���: 2.5_ReferenceCounting.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkObject.h>

// MyFunction��������ʾ����ָ�������Ϊ��������ֵ
vtkSmartPointer<vtkImageData> MyFunction()
{
	vtkSmartPointer<vtkImageData> myObject = vtkSmartPointer<vtkImageData>::New();
	std::cout<<"MyFunction::myObject reference count = "<<myObject->GetReferenceCount()<<std::endl;
	return myObject;
}

//�����ļ���data/VTK-logo.bmp
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"BMP-File(*.bmp)"<<std::endl;
		return EXIT_FAILURE;
	}
	//��ʾ���ü�����
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	std::cout<<"Reference Count of reader->GetOutput (Before Assignment) = "
		<<reader->GetOutput()->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkImageData> image1 = reader->GetOutput();
	std::cout<<"Reference Count of reader->GetOutput (Assign to image1) = "
		<<reader->GetOutput()->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of image1 = "
		<<image1->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkImageData> image2 = reader->GetOutput();
	std::cout<<"Reference Count of reader->GetOutput (Assign to image2) = "
		<<reader->GetOutput()->GetReferenceCount()<<std::endl;
	std::cout<<"Reference Count of image2 = "
		<<image2->GetReferenceCount()<<std::endl;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//��ʾ����ָ�������Ϊ��������ֵ
	//���ں���MyFunction()�ķ���ֵ��ͨ�������ķ�ʽ��
	//�����ݸ�����õı�������˸����ݵ����ü������ֲ���
	std::cout<<"myObject reference count = "
		<<MyFunction()->GetReferenceCount()<<std::endl;

	vtkSmartPointer<vtkImageData> MyImageData = MyFunction();
	std::cout<<"MyFunction return value reference count = "
		<<MyFunction()->GetReferenceCount()<<std::endl;

	std::cout<<"MyImageData reference count = "
		<<MyImageData->GetReferenceCount()<<std::endl;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//���û�и���������ڴ棬��Ȼ����ʹ������ָ��:
	vtkSmartPointer<vtkBMPReader> Reader = vtkSmartPointer<vtkBMPReader>::New();
	vtkImageData* pd = Reader->GetOutput();
	//////////////////////////////////////////////////////////////////////////

	system("pause");
	return EXIT_SUCCESS;
}