/**********************************************************************

  �ļ���: vtkTestFilter.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h

#include "vtkPolyDataAlgorithm.h"

#define MyEvent (vtkCommand::UserEvent+1)

class vtkTestFilter : public vtkPolyDataAlgorithm
{
public:
	vtkTypeMacro(vtkTestFilter,vtkPolyDataAlgorithm);
	static vtkTestFilter *New();

protected:
	vtkTestFilter();
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
	int m_Value;

private:
	vtkTestFilter(const vtkTestFilter&);  // Not implemented.
	void operator=(const vtkTestFilter&);  // Not implemented.

};
#endif