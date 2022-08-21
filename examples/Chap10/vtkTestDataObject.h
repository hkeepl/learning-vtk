/**********************************************************************

  �ļ���: vtkTestDataObject.h
  Copyright (c) ������, �޻���. All rights reserved.
  ������Ϣ�����: 
    http://www.vtkchina.org (VTK�й�)
	http://blog.csdn.net/www_doling_net (���鹤����) 

**********************************************************************/

#ifndef __vtkTestDataObject_h
#define __vtkTestDataObject_h

#include "vtkDataObject.h"

class vtkTestDataObject : public vtkDataObject
{
public:
	static vtkTestDataObject* New();
	vtkTypeMacro(vtkTestDataObject,vtkDataObject);

	void PrintSelf( ostream& os, vtkIndent indent );
	void ShallowCopy(vtkTestDataObject* t);

	vtkGetMacro(Value, double);
	vtkSetMacro(Value, double);

protected:
	vtkTestDataObject();
	~vtkTestDataObject();

private:
	vtkTestDataObject( const vtkTestDataObject& ); // Not implemented.
	void operator = ( const vtkTestDataObject& ); // Not implemented.

	double Value;
};

#endif