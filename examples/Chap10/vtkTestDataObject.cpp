/**********************************************************************

  �ļ���: vtkTestDataObject.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include "vtkTestDataObject.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkTestDataObject);

vtkTestDataObject::vtkTestDataObject()
{
	this->Value = 0.0;
}

vtkTestDataObject::~vtkTestDataObject()
{
}

void vtkTestDataObject::PrintSelf( ostream& os, vtkIndent indent )
{
	this->Superclass::PrintSelf( os, indent );
}

void vtkTestDataObject::ShallowCopy(vtkTestDataObject* t)
{
	this->Value = t->GetValue(); 
}