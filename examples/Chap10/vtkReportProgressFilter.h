/**********************************************************************

  �ļ���: vtkReportProgressFilter.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef __vtkReportProgressFilter_h
#define __vtkReportProgressFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkReportProgressFilter : public vtkPolyDataAlgorithm 
{
public:
	vtkTypeMacro(vtkReportProgressFilter,vtkPolyDataAlgorithm);

	static vtkReportProgressFilter *New();

protected:
	vtkReportProgressFilter(){}
	~vtkReportProgressFilter(){}

	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
	vtkReportProgressFilter(const vtkReportProgressFilter&);  // Not implemented.
	void operator=(const vtkReportProgressFilter&);  // Not implemented.
};

#endif