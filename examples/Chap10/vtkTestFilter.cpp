/**********************************************************************

  �ļ���: vtkTestFilter.cpp
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#include "vtkObjectFactory.h"
#include "vtkCommand.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkTestFilter.h"

vtkStandardNewMacro(vtkTestFilter);

vtkTestFilter::vtkTestFilter()
{
	this->SetNumberOfInputPorts(0);

	m_Value = 10;
}

int vtkTestFilter::RequestData(vtkInformation *vtkNotUsed(request),
							   vtkInformationVector **inputVector,
							   vtkInformationVector *outputVector)
{
	this->InvokeEvent(MyEvent, &m_Value);
	return 1;
}