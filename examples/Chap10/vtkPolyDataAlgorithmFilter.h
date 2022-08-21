/**********************************************************************

  �ļ���: vtkPolyDataAlgorithmFilter.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkPolyDataAlgorithmFilter : public vtkPolyDataAlgorithm
{
public:
	vtkTypeMacro(vtkPolyDataAlgorithmFilter,vtkPolyDataAlgorithm);
	void PrintSelf(ostream& os, vtkIndent indent);

	static vtkPolyDataAlgorithmFilter *New();

protected:
	vtkPolyDataAlgorithmFilter(){}
	~vtkPolyDataAlgorithmFilter(){}

	int FillInputPortInformation( int port, vtkInformation* info );
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
	vtkPolyDataAlgorithmFilter(const vtkPolyDataAlgorithmFilter&);  // Not implemented.
	void operator=(const vtkPolyDataAlgorithmFilter&);  // Not implemented.
};

#endif